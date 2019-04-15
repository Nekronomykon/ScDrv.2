/*=========================================================================

  Program:   Visualization Toolkit Local Fork
  Module:    MoleculeMapper.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "MoleculeMapper.h"

#include <vtkActor.h>
#include <vtkColor.h>
#include <vtkCylinderSource.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkEventForwarderCommand.h>
#include <vtkExecutive.h>
#include <vtkFloatArray.h>
#include <vtkGlyph3DMapper.h>
#include <vtkIdTypeArray.h>
#include <vtkInformation.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkMolecule.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPeriodicTable.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTrivialProducer.h>
#include <vtkUnsignedCharArray.h>
#include <vtkUnsignedShortArray.h>
#include <vtkVector.h>
#include <vtkVectorOperators.h>
#include <vtkStringArray.h>

using namespace vtk;

const MoleculeMapperStyle MoleculeMapper::styleFast =
    {true, MoleculeMapperStyle::UnitRadius, 0.4f, true, false, MoleculeMapperStyle::SingleColor, 0.125f, 64, 64, 64};
const MoleculeMapperStyle MoleculeMapper::styleBallSticks =
    {true, MoleculeMapperStyle::VDWRadius, 0.25f, true, false, MoleculeMapperStyle::DiscreteByAtom, 0.125f, 0, 0, 0};
const MoleculeMapperStyle MoleculeMapper::styleCPK =
    {true, MoleculeMapperStyle::VDWRadius, 1.0f, false, false, 0, 0};
const MoleculeMapperStyle MoleculeMapper::styleSticks =
    {true, MoleculeMapperStyle::UnitRadius, 0.15f, true, false, MoleculeMapperStyle::DiscreteByAtom, 0.15f};

// Note this class may have an accelerated subclass ala
// vtkOpenGLMoleculeMapper. If you change this class please
// also check that class for impacts.
vtkObjectFactoryNewMacro(MoleculeMapper);

//----------------------------------------------------------------------------
MoleculeMapper::MoleculeMapper()
    : glyphAtoms_(/* Glyph3DMap::New() */), glyphBonds_(/* Glyph3DMap::New() */), styleMap_(styleFast), AtomicRadiusArrayName(nullptr), RenderLattice(false), GlyphDataInitialized(false), areLabelDataInitialized_(false), pad_(2)
{
  // Initialize ivars:
  this->BondColor[0] = this->BondColor[1] = this->BondColor[2] = 64; // ???
  this->ResetStyleToDefault();
  this->LatticeColor[0] = this->LatticeColor[1] = this->LatticeColor[2] = 255;
  this->SetAtomicRadiusArrayName("radii");

  // Setup glyph sources
  vtkNew<vtkSphereSource> sphere;
  sphere->SetRadius(1.0);
  sphere->SetPhiResolution(50);
  sphere->SetThetaResolution(50);
  sphere->Update();
  this->glyphAtoms_->SetSourceConnection(sphere->GetOutputPort());

  vtkNew<vtkCylinderSource> cylinder;
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(20);
  cylinder->SetHeight(1.0);
  cylinder->CappingOff();
  cylinder->Update();
  // Rotate the glyph so that the cylinder is aligned with the x-axis,
  // rather than the y-axis. This makes glyph orientation much easier.
  vtkNew<vtkTransform> cylXform;
  cylXform->RotateWXYZ(90, 0.0, 0.0, 1.0);
  vtkNew<vtkTransformPolyDataFilter> cylXformFilter;
  cylXformFilter->SetInputConnection(cylinder->GetOutputPort());
  cylXformFilter->SetTransform(cylXform);
  cylXformFilter->Update();
  this->glyphBonds_->SetSourceConnection(cylXformFilter->GetOutputPort());

  // Configure default LookupTable
  vtkNew<vtkLookupTable> lut;
  this->PeriodicTable->GetDefaultLUT(lut);
  this->SetLookupTable(lut);

  // Setup glyph mappers
  this->glyphAtoms_->SetScalarRange(0, this->PeriodicTable->GetNumberOfElements());
  this->glyphAtoms_->SetColorModeToMapScalars();
  this->glyphAtoms_->SetScalarModeToUsePointFieldData();
  this->glyphAtoms_->SetScaleModeToScaleByMagnitude();
  this->glyphBonds_->SetScaleModeToScaleByVectorComponents();
  // Bond color mode is setup during updates

  // Forward commands to instance mappers
  vtkNew<vtkEventForwarderCommand> cb;
  cb->SetTarget(this);

  this->glyphAtoms_->AddObserver(vtkCommand::StartEvent, cb);
  this->glyphAtoms_->AddObserver(vtkCommand::EndEvent, cb);
  this->glyphAtoms_->AddObserver(vtkCommand::ProgressEvent, cb);

  this->glyphBonds_->AddObserver(vtkCommand::StartEvent, cb);
  this->glyphBonds_->AddObserver(vtkCommand::EndEvent, cb);
  this->glyphBonds_->AddObserver(vtkCommand::ProgressEvent, cb);

  // Connect the trivial producers to forward the glyph polydata
  this->AtomGlyphPointOutput->SetOutput(this->AtomGlyphPolyData);
  this->glyphAtoms_->SetInputConnection(this->AtomGlyphPointOutput->GetOutputPort());

  this->BondGlyphPointOutput->SetOutput(this->BondGlyphPolyData);
  this->glyphBonds_->SetInputConnection(this->BondGlyphPointOutput->GetOutputPort());

  this->LatticeMapper->SetInputData(this->LatticePolyData);
  this->LatticeMapper->SetColorModeToDefault();

  // Force the glyph data to be generated on the next render:
  // this->GlyphDataInitialized = false;

  this->SetInputArrayToProcess(0, 0, 0,
                               vtkDataObject::FIELD_ASSOCIATION_VERTICES,
                               "Atomic Numbers");
}

//----------------------------------------------------------------------------
MoleculeMapper::~MoleculeMapper()
{
  this->SetLookupTable(nullptr);
  this->SetAtomicRadiusArrayName(nullptr);
}

//----------------------------------------------------------------------------
void MoleculeMapper::SetInputData(vtkMolecule *input)
{
  this->SetInputDataInternal(0, input);
}

//----------------------------------------------------------------------------
vtkMolecule *MoleculeMapper::GetInput()
{
  return vtkMolecule::SafeDownCast(this->GetExecutive()->GetInputData(0, 0));
}

//----------------------------------------------------------------------------
void MoleculeMapper::GetSelectedAtomsAndBonds(vtkSelection *selection,
                                              vtkIdTypeArray *atomIds,
                                              vtkIdTypeArray *bondIds)
{
  // Sanity check
  if (!selection)
    return;
  if (!atomIds && (!bondIds))
    return;

  // Clear the inputs
  if (atomIds)
    atomIds->Reset();
  if (bondIds)
    bondIds->Reset();

  const vtkIdType numAtoms = this->GetInput()->GetNumberOfAtoms();
  const vtkIdType numBonds = this->GetInput()->GetNumberOfBonds();
  const vtkIdType numAtomsAndBonds = numAtoms + numBonds;

  // Find selection node that we're interested in:
  const vtkIdType numNodes = selection->GetNumberOfNodes();
  for (vtkIdType nodeId = 0; nodeId < numNodes; ++nodeId)
  {
    vtkSelectionNode *node = selection->GetNode(nodeId);

    // Check if the mapper is this instance of MoleculeMapper
    vtkActor *selActor = vtkActor::SafeDownCast(
        node->GetProperties()->Get(vtkSelectionNode::PROP()));

    if (selActor && (selActor->GetMapper() == this))
    {
      // Separate the selection ids into atoms and bonds
      vtkIdTypeArray *selIds = vtkArrayDownCast<vtkIdTypeArray>(
          node->GetSelectionList());
      if (selIds)
      {
        vtkIdType numIds = selIds->GetNumberOfTuples();
        for (vtkIdType i = 0; i < numIds; ++i)
        {
          vtkIdType curId = selIds->GetValue(i);
          if (atomIds != nullptr && curId < numAtoms) // atoms
          {
            atomIds->InsertNextValue(curId);
          }
          else if (bondIds != nullptr && curId < numAtomsAndBonds) // bonds
          {
            // Remove offset
            curId -= numAtoms;
            bondIds->InsertNextValue(curId);
          }
        }
      }
    }
  }
}

//----------------------------------------------------------------------------
void MoleculeMapper::Render(vtkRenderer *ren, vtkActor *act)
{
  // If we add more rendering backend (e.g. point sprites), add a switch here.
  this->GlyphRender(ren, act);
}

//----------------------------------------------------------------------------
void MoleculeMapper::GlyphRender(vtkRenderer *ren, vtkActor *act)
{
  // Update cached polydata if needed
  this->UpdateGlyphPolyData();

  // Pass rendering call on
  if (styleMap_.HasToRenderAtoms())
  {
    this->glyphAtoms_->Render(ren, act);
  }

  if (this->GetStyle().HasToRenderBonds())
  {
    this->glyphBonds_->Render(ren, act);
  }

  if (this->RenderLattice)
  {
    this->LatticeMapper->Render(ren, act);
  }
}

//----------------------------------------------------------------------------
void MoleculeMapper::UpdateGlyphPolyData()
{
  vtkMolecule *molecule = this->GetInput();

  if (!this->GlyphDataInitialized || ((molecule->GetMTime() > this->AtomGlyphPolyData->GetMTime() || this->GetMTime() > this->AtomGlyphPolyData->GetMTime() || this->LookupTable->GetMTime() > this->AtomGlyphPolyData->GetMTime()) && this->GetStyle().HasToRenderAtoms()))
  {
    this->UpdateAtomGlyphPolyData();
  }

  if (!this->GlyphDataInitialized || ((molecule->GetMTime() > this->BondGlyphPolyData->GetMTime() || this->GetMTime() > this->BondGlyphPolyData->GetMTime() || this->LookupTable->GetMTime() > this->BondGlyphPolyData->GetMTime()) &&
                                      this->GetStyle().HasToRenderBonds()))
  {
    this->UpdateBondGlyphPolyData();
  }

  if (!this->GlyphDataInitialized || ((molecule->GetMTime() > this->LatticePolyData->GetMTime() ||
                                       this->GetMTime() > this->LatticePolyData->GetMTime()) &&
                                      this->RenderLattice))
  {
    this->UpdateLatticePolyData();
  }

  this->GlyphDataInitialized = true;
}

//----------------------------------------------------------------------------
// Generate scale and position information for each atom sphere
void MoleculeMapper::UpdateAtomGlyphPolyData()
{
  this->AtomGlyphPolyData->Initialize();

  vtkMolecule *molecule = this->GetInput();

  int assoc; // output var for GetInputAbstractArrayToProcess
  vtkAbstractArray *wholeColorArray =
      this->GetInputAbstractArrayToProcess(0, molecule, assoc);

  vtkAbstractArray *colorArray = wholeColorArray != nullptr ? wholeColorArray->NewInstance() : nullptr;

  vtkNew<vtkUnsignedShortArray> atomicNbWithoutGhostArray;
  vtkUnsignedShortArray *atomicNbFullArray = molecule->GetAtomicNumberArray();
  vtkNew<vtkPoints> points;
  vtkPoints *allPoints = molecule->GetAtomicPositionArray();
  vtkUnsignedCharArray *ghosts = molecule->GetAtomGhostArray();
  for (vtkIdType i = 0; i < molecule->GetNumberOfAtoms(); i++)
  {
    /**
     * Skip ghost atoms but not ghost bonds:
     *  - each atom is non-ghost for exactly one MPI node, that will handle it.
     *  - a ghost bond links an atom and a ghost atom. So there is exactly two MPI nodes
     *    that contain this ghost bond and no one that contains this bond as non-ghost.
     *    We let this two MPI nodes handle the ghost bond, as we cannot know if the bond
     *    was already handled.
     */
    if (ghosts && ghosts->GetValue(i) == 1)
    {
      continue;
    }
    atomicNbWithoutGhostArray->InsertNextValue(atomicNbFullArray->GetValue(i));
    points->InsertNextPoint(allPoints->GetPoint(i));
    if (colorArray != nullptr)
    {
      colorArray->InsertNextTuple(i, wholeColorArray);
    }
  }
  const vtkIdType numAtoms = points->GetNumberOfPoints();

  if (colorArray != nullptr)
  {
    if (colorArray->GetNumberOfTuples() != numAtoms)
    {
      vtkErrorMacro("Color array size does not match number of atoms.");
    }
    else
    {
      int colorArrayIdx =
          this->AtomGlyphPolyData->GetPointData()->AddArray(colorArray);
      this->glyphAtoms_->SelectColorArray(colorArrayIdx);
    }
    colorArray->Delete();
  }

  this->AtomGlyphPolyData->SetPoints(points.Get());
  this->glyphAtoms_->SetLookupTable(this->LookupTable);

  vtkNew<vtkFloatArray> scaleFactors;
  scaleFactors->SetNumberOfComponents(1);
  scaleFactors->SetName("Scale Factors");
  scaleFactors->Allocate(numAtoms);

  switch (this->GetStyle().GetAtomicRadiusType())
  {
  default:
    vtkWarningMacro(<< "Unknown radius type: " << this->GetStyle().GetAtomicRadiusType()
                    << ". Falling back to 'VDWRadius' (" << MMStyle::VDWRadius << ").");
    VTK_FALLTHROUGH;
  case (MMStyle::VDWRadius):
    for (vtkIdType i = 0; i < numAtoms; ++i)
    {
      scaleFactors->InsertNextValue(this->GetStyle().GetAtomicRadiusScale() *
                                    this->PeriodicTable->GetVDWRadius(atomicNbWithoutGhostArray->GetValue(i)));
    }
    break;
  case (MMStyle::CovalentRadius):
    for (vtkIdType i = 0; i < numAtoms; ++i)
    {
      scaleFactors->InsertNextValue(this->GetStyle().GetAtomicRadiusScale() *
                                    this->PeriodicTable->GetCovalentRadius(atomicNbWithoutGhostArray->GetValue(i)));
    }
    break;
  case (MMStyle::UnitRadius):
    for (vtkIdType i = 0; i < numAtoms; ++i)
    {
      scaleFactors->InsertNextValue(this->GetStyle().GetAtomicRadiusScale());
    }
    break;
  case (MMStyle::CustomArrayRadius):
  {
    vtkDataArray *allRadii = molecule->GetVertexData()->GetArray(this->AtomicRadiusArrayName);
    if (!allRadii)
    {
      vtkWarningMacro("AtomicRadiusType set to CustomArrayRadius, but no "
                      "array named "
                      << this->AtomicRadiusArrayName << " found in input VertexData.");
      scaleFactors->SetNumberOfTuples(numAtoms);
      scaleFactors->FillComponent(0, this->GetStyle().GetAtomicRadiusScale());
      break;
    }
    vtkNew<vtkDoubleArray> radii;
    for (vtkIdType i = 0; i < molecule->GetNumberOfAtoms(); i++)
    {
      if (ghosts && ghosts->GetValue(i) == 1)
      {
        continue;
      }
      radii->InsertNextValue(allRadii->GetTuple1(i));
    }
    if (radii->GetNumberOfTuples() != numAtoms)
    {
      vtkWarningMacro("'radii' array contains " << radii->GetNumberOfTuples()
                                                << " entries, but there are " << numAtoms << " atoms.");
      scaleFactors->SetNumberOfTuples(numAtoms);
      scaleFactors->FillComponent(0, this->GetStyle().GetAtomicRadiusScale());
    }
    else
    {
      scaleFactors->DeepCopy(radii);
      scaleFactors->SetName("Scale Factors"); // copy resets name.
    }
    break;
  }
  }

  this->AtomGlyphPolyData->GetPointData()->AddArray(scaleFactors);
  this->glyphAtoms_->SetScaleArray("Scale Factors");
}

//----------------------------------------------------------------------------
// Generate position, scale, and orientation vectors for each bond cylinder
void MoleculeMapper::UpdateBondGlyphPolyData()
{
  this->BondGlyphPolyData->Initialize();

  vtkMolecule *molecule = this->GetInput();
  const vtkIdType numBonds = molecule->GetNumberOfBonds();

  // For selection ID offset:
  const vtkIdType numAtoms = molecule->GetNumberOfAtoms();

  // Create arrays
  vtkNew<vtkPoints> cylCenters;
  vtkNew<vtkFloatArray> cylScales;
  vtkNew<vtkFloatArray> orientationVectors;
  // Since vtkHardwareSelector won't distinguish between the internal instance
  // mappers of MoleculeMapper, use a custom selection ID range. This also
  // fixes the issue of bonds that are colored-by-atom, as these are rendered
  // as two glyphs.
  vtkNew<vtkIdTypeArray> selectionIds;

  // Setup arrays
  // vtkPoints uses three components by default
  cylScales->SetNumberOfComponents(3);
  orientationVectors->SetNumberOfComponents(3);
  selectionIds->SetNumberOfComponents(1);

  // Name arrays
  // Can't set name for points
  cylScales->SetName("Scale Factors");
  orientationVectors->SetName("Orientation Vectors");
  selectionIds->SetName("Selection Ids");

  // Allocate memory -- find out how many cylinders are needed
  vtkIdType numCylinders = numBonds;
  // Up to three cylinders per bond if multicylinders are enabled:
  if (this->GetStyle().IsMultiBonds())
  {
    numCylinders *= 3;
  }
  // If DiscreteByAtom coloring is used, each cylinder is represented
  // by two individual cylinders
  if (this->GetStyle().GetTypeBondsColor() == MMStyle::DiscreteByAtom)
  {
    numCylinders *= 2;
  }

  // Allocate memory. Multiply numCylinders by number of components in array.
  cylCenters->Allocate(3 * numCylinders);
  cylScales->Allocate(3 * numCylinders);
  orientationVectors->Allocate(3 * numCylinders);
  selectionIds->Allocate(numCylinders);

  // Add arrays to BondGlyphPolyData
  this->BondGlyphPolyData->SetPoints(cylCenters);
  this->BondGlyphPolyData->GetPointData()->AddArray(cylScales);
  this->BondGlyphPolyData->GetPointData()->AddArray(
      orientationVectors);
  this->BondGlyphPolyData->GetPointData()->AddArray(
      selectionIds);

  // Set up coloring mode
  vtkDataArray *cylColors = nullptr;
  switch (this->GetStyle().GetTypeBondsColor())
  {
  case (MMStyle::SingleColor):
    cylColors = vtkUnsignedCharArray::New();
    cylColors->SetNumberOfComponents(3);
    cylColors->Allocate(3 * numCylinders);
    cylColors->SetName("Colors");
    this->BondGlyphPolyData->GetPointData()->SetScalars(cylColors);
    this->glyphBonds_->SetColorModeToDefault();
    this->glyphBonds_->SetScalarModeToUsePointData();
    break;
  default:
  case (MMStyle::DiscreteByAtom):
    cylColors = vtkUnsignedShortArray::New();
    cylColors->SetNumberOfComponents(1);
    cylColors->Allocate(numCylinders);
    cylColors->SetName("Colors");
    this->BondGlyphPolyData->GetPointData()->SetScalars(cylColors);
    this->glyphBonds_->SetLookupTable(this->LookupTable);
    this->glyphBonds_->SetScalarRange(0, this->PeriodicTable->GetNumberOfElements());
    this->glyphBonds_->SetScalarModeToUsePointData();
    this->glyphAtoms_->SetColorModeToMapScalars();
    break;
  }

  // Set up pointers to the specific color arrays
  vtkUnsignedCharArray *singleColorArray =
      vtkArrayDownCast<vtkUnsignedCharArray>(cylColors);
  vtkUnsignedShortArray *discreteColorArray =
      vtkArrayDownCast<vtkUnsignedShortArray>(cylColors);

  // Remove reference to cylColors
  cylColors->Delete();

  // Declare some variables for later
  unsigned short bondOrder;
  float bondLength;
  // Since the input cylinder is oriented along the z axis, the
  // scale vector should be [radius, radius, bondLength]
  vtkVector3f scale;
  // Current cylinder's selection id
  vtkIdType selectionId;
  // Distance between multicylinder surfaces is approx. 1/3 of the
  // diameter:
  const float deltaLength = this->GetStyle().GetBondRadius() * 2.6;
  // Vector between centers cylinders in a multibond:
  vtkVector3f delta;
  delta.Set(0.0, 0.0, 0.0);
  // The initial displacement when generating a multibond
  vtkVector3f initialDisp;
  initialDisp.Set(0.0, 0.0, 0.0);
  // The geometric center of the bond
  vtkVector3f bondCenter;
  // The center of the current cylinder
  vtkVector3f cylinderCenter;
  // Used in DiscreteByAtom color mode:
  vtkVector3f halfCylinderCenter;
  // The positions of the start and end atoms
  vtkVector3f pos1, pos2;
  // Array containing the atomic numbers of {begin, end} atoms
  unsigned short atomicNumbers[2];
  // Normalized vector pointing along bond from begin->end atom
  vtkVector3f bondVec;
  // Unit z vector -- used for multicylinder orientation
  static const vtkVector3f unitZ(0.0, 0.0, 1.0);
  // Can't use InsertNextTuple(unsigned char *) in a
  // vtkUnsignedCharArray. This float array is used instead.
  // Initialize with bondColor for SingleColor mode
  vtkColor3f bondColorf(static_cast<float>(this->BondColor[0]),
                        static_cast<float>(this->BondColor[1]),
                        static_cast<float>(this->BondColor[2]));

  // Generate the scale, orientation, and position of each cylinder
  for (vtkIdType bondInd = 0; bondInd < numBonds; ++bondInd)
  {
    selectionId = numAtoms + bondInd; // mixing 1 and 0 indexed ids on purpose
    // Extract bond info
    vtkBond bond = molecule->GetBond(bondInd);
    bondOrder = bond.GetOrder();
    pos1 = bond.GetBeginAtom().GetPosition();
    pos2 = bond.GetEndAtom().GetPosition();
    atomicNumbers[0] = bond.GetBeginAtom().GetAtomicNumber();
    atomicNumbers[1] = bond.GetEndAtom().GetAtomicNumber();

    // Compute additional bond info
    // - Normalized vector in direction of bond
    bondVec = pos2 - pos1;
    bondLength = bondVec.Normalize();
    // - Center of bond for translation
    // TODO vtkVector scalar multiplication
    //    bondCenter = (pos1 + pos2) * 0.5;
    bondCenter[0] = (pos1[0] + pos2[0]) * 0.5;
    bondCenter[1] = (pos1[1] + pos2[1]) * 0.5;
    bondCenter[2] = (pos1[2] + pos2[2]) * 0.5;
    // end vtkVector TODO

    // Set up delta step vector and bond radius from bond order:
    if (this->GetStyle().IsMultiBonds())
    {
      switch (bondOrder)
      {
      case 1:
      default:
        delta.Set(0.0, 0.0, 0.0);
        initialDisp.Set(0.0, 0.0, 0.0);
        break;
      case 2:
        // TODO vtkVector scalar multiplication
        //          delta = bondVec.Cross(unitZ).Normalized() * deltaLength;
        //          initialDisp = delta * (-0.5);
        delta = bondVec.Cross(unitZ).Normalized();
        delta[0] *= deltaLength;
        delta[1] *= deltaLength;
        delta[2] *= deltaLength;
        initialDisp.Set(delta[0] * (-0.5), delta[1] * (-0.5), delta[2] * (-0.5));
        // End vtkVector TODO
        break;
      case 3:
        // TODO vtkVector scalar multiplication, negation
        //          delta = bondVec.Cross(unitZ).Normalized() * deltaLength;
        //          initialDisp = -delta;
        delta = bondVec.Cross(unitZ).Normalized();
        delta[0] *= deltaLength;
        delta[1] *= deltaLength;
        delta[2] *= deltaLength;
        initialDisp.Set(-delta[0], -delta[1], -delta[2]);
        // End vtkVector TODO
        break;
      }
    }

    // Set up cylinder scale factors
    float R = this->GetStyle().GetBondRadius();
    switch (this->GetStyle().GetTypeBondsColor())
    {
    case (MMStyle::SingleColor):
      scale.Set(bondLength, R, R);
      break;
    default:
    case (MMStyle::DiscreteByAtom):
      scale.Set(0.5 * bondLength, R, R);
      break;
    }

    if (this->GetStyle().IsMultiBonds())
    {
      cylinderCenter = bondCenter + initialDisp;
    }
    else
    {
      cylinderCenter = bondCenter;
    }

    // For each bond order, add a point to the glyph points, translate
    // by delta, and repeat.
    for (unsigned short iter = 0; iter < bondOrder; ++iter)
    {
      // Single color mode adds a single cylinder, while
      // DiscreteByAtom adds two differently colored and positioned
      // cylinders.
      switch (this->GetStyle().GetTypeBondsColor())
      {
      case (MMStyle::SingleColor):
        cylCenters->InsertNextPoint(cylinderCenter.GetData());
        cylScales->InsertNextTuple(scale.GetData());
        singleColorArray->InsertNextTuple(bondColorf.GetData());
        orientationVectors->InsertNextTuple(bondVec.GetData());
        selectionIds->InsertNextValue(selectionId);
        break;
      default:
      case (MMStyle::DiscreteByAtom):
        // Cache some scaling factors
        const float quarterLength = 0.25 * bondLength;

        // Add cylinder for begin atom:
        // TODO vtkVector subtraction, scalar multiplication
        //          halfCylinderCenter = cylinderCenter - (bondVec * quarterLength);
        halfCylinderCenter[0] = cylinderCenter[0] -
                                (bondVec[0] * quarterLength);
        halfCylinderCenter[1] = cylinderCenter[1] -
                                (bondVec[1] * quarterLength);
        halfCylinderCenter[2] = cylinderCenter[2] -
                                (bondVec[2] * quarterLength);
        // end vtkVector TODO

        cylCenters->InsertNextPoint(halfCylinderCenter.GetData());
        cylScales->InsertNextTuple(scale.GetData());
        discreteColorArray->InsertNextValue(atomicNumbers[0]);
        orientationVectors->InsertNextTuple(bondVec.GetData());
        selectionIds->InsertNextValue(selectionId);

        // Add cylinder for begin atom:
        // TODO vtkVector addition, scalar multiplication
        //          halfCylinderCenter = cylinderCenter + (bondVec * quarterLength);
        halfCylinderCenter[0] = cylinderCenter[0] +
                                (bondVec[0] * quarterLength);
        halfCylinderCenter[1] = cylinderCenter[1] +
                                (bondVec[1] * quarterLength);
        halfCylinderCenter[2] = cylinderCenter[2] +
                                (bondVec[2] * quarterLength);
        // end vtkVector TODO

        cylCenters->InsertNextPoint(halfCylinderCenter.GetData());
        cylScales->InsertNextTuple(scale.GetData());
        discreteColorArray->InsertNextValue(atomicNumbers[1]);
        orientationVectors->InsertNextTuple(bondVec.GetData());
        selectionIds->InsertNextValue(selectionId);
      }

      // Prepare for next multicylinder
      if (this->GetStyle().IsMultiBonds() && bondOrder != 1)
      {
        // TODO vtkVector in-place addition
        //        cylinderCenter += delta;
        cylinderCenter[0] += delta[0];
        cylinderCenter[1] += delta[1];
        cylinderCenter[2] += delta[2];
        // end vtkVector TODO
      }
    }
  }

  // Free up some space
  this->BondGlyphPolyData->Squeeze();

  // Setup glypher
  this->glyphBonds_->SetScaleArray("Scale Factors");
  this->glyphBonds_->SetOrientationArray("Orientation Vectors");
  this->glyphBonds_->SetSelectionIdArray("Selection Ids");
  this->glyphBonds_->UseSelectionIdsOn();
}

//----------------------------------------------------------------------------
void MoleculeMapper::UpdateAtomLabel()
{
  dataAtomsLabel_->Initialize();
  vtkMolecule *molecule = this->GetInput();
}

//----------------------------------------------------------------------------
void MoleculeMapper::UpdateBondLabel()
{
  dataBondsLabel_->Initialize();
  vtkMolecule *molecule = this->GetInput();
}

//----------------------------------------------------------------------------
void MoleculeMapper::UpdateLatticePolyData()
{
  this->LatticePolyData->Initialize();

  vtkMolecule *molecule = this->GetInput();
  if (!molecule->HasLattice())
  {
    return;
  }

  vtkVector3d a;
  vtkVector3d b;
  vtkVector3d c;
  vtkVector3d origin;

  molecule->GetLattice(a, b, c, origin);

  vtkNew<vtkPoints> points;
  points->SetNumberOfPoints(8);
  points->SetPoint(0, origin.GetData());
  points->SetPoint(1, (origin + a).GetData());
  points->SetPoint(2, (origin + b).GetData());
  points->SetPoint(3, (origin + c).GetData());
  points->SetPoint(4, (origin + a + b).GetData());
  points->SetPoint(5, (origin + a + c).GetData());
  points->SetPoint(6, (origin + b + c).GetData());
  points->SetPoint(7, (origin + a + b + c).GetData());
  this->LatticePolyData->SetPoints(points);

  vtkNew<vtkUnsignedCharArray> latticeColors;
  latticeColors->SetNumberOfComponents(3);
  latticeColors->SetNumberOfTuples(8);
  for (vtkIdType i = 0; i < 8; ++i)
  {
    latticeColors->SetTypedTuple(i, this->LatticeColor);
  }
  this->LatticePolyData->GetPointData()->SetScalars(latticeColors);

  vtkNew<vtkCellArray> lines;
  vtkIdType line[2];

  line[0] = 0;
  line[1] = 1;
  lines->InsertNextCell(2, line);
  line[0] = 1;
  line[1] = 4;
  lines->InsertNextCell(2, line);
  line[0] = 4;
  line[1] = 2;
  lines->InsertNextCell(2, line);
  line[0] = 2;
  line[1] = 0;
  lines->InsertNextCell(2, line);
  line[0] = 0;
  line[1] = 3;
  lines->InsertNextCell(2, line);
  line[0] = 2;
  line[1] = 6;
  lines->InsertNextCell(2, line);
  line[0] = 4;
  line[1] = 7;
  lines->InsertNextCell(2, line);
  line[0] = 1;
  line[1] = 5;
  lines->InsertNextCell(2, line);
  line[0] = 6;
  line[1] = 3;
  lines->InsertNextCell(2, line);
  line[0] = 5;
  line[1] = 3;
  lines->InsertNextCell(2, line);
  line[0] = 5;
  line[1] = 7;
  lines->InsertNextCell(2, line);
  line[0] = 6;
  line[1] = 7;
  lines->InsertNextCell(2, line);

  this->LatticePolyData->SetLines(lines);
}

//----------------------------------------------------------------------------
void MoleculeMapper::ReleaseGraphicsResources(vtkWindow *w)
{
  this->glyphAtoms_->ReleaseGraphicsResources(w);
  this->glyphBonds_->ReleaseGraphicsResources(w);
}

double *MoleculeMapper::GetBounds()
{
  vtkMolecule *input = this->GetInput();
  if (!input)
  {
    vtkMath::UninitializeBounds(this->Bounds);
  }
  else
  {
    if (!this->Static)
    {
      this->Update();
    }
    input->GetBounds(this->Bounds);
    // Pad bounds by several Angstrom to contain spheres, etc
    this->Bounds[0] -= pad_;
    this->Bounds[1] += pad_;
    this->Bounds[2] -= pad_;
    this->Bounds[3] += pad_;
    this->Bounds[4] -= pad_;
    this->Bounds[5] += pad_;
  }
  return this->Bounds;
}

//----------------------------------------------------------------------------
int MoleculeMapper::FillInputPortInformation(int vtkNotUsed(port), vtkInformation *info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkMolecule");
  return 1;
}

//----------------------------------------------------------------------------
void MoleculeMapper::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "AtomGlyphMapper:\n";
  this->glyphAtoms_->PrintSelf(os, indent.GetNextIndent());

  os << indent << "BondGlyphMapper:\n";
  this->glyphBonds_->PrintSelf(os, indent.GetNextIndent());
}
