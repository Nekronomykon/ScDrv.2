/*=========================================================================

  Program:   Visualization Toolkit

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "MoleculeMapperOpenGL.h"

#include <vtkOpenGLSphereMapper.h>
#include <vtkOpenGLStickMapper.h>

#include <vtkEventForwarderCommand.h>
#include <vtkGlyph3DMapper.h>
#include <vtkLookupTable.h>
#include <vtkMolecule.h>
#include <vtkObjectFactory.h>
#include <vtkPeriodicTable.h>
#include <vtkTrivialProducer.h>

using namespace vtk;

//-----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeMapperOpenGL)

    //----------------------------------------------------------------------------
    MoleculeMapperOpenGL::MoleculeMapperOpenGL()
{
  // Setup glyph mappers
  this->FastAtomMapper->SetScalarRange(0, this->PeriodicTable->GetNumberOfElements());
  this->FastAtomMapper->SetColorModeToMapScalars();
  this->FastAtomMapper->SetScalarModeToUsePointFieldData();

  // Forward commands to instance mappers
  vtkNew<vtkEventForwarderCommand> cb;
  cb->SetTarget(this);

  this->FastAtomMapper->AddObserver(vtkCommand::StartEvent, cb);
  this->FastAtomMapper->AddObserver(vtkCommand::EndEvent, cb);
  this->FastAtomMapper->AddObserver(vtkCommand::ProgressEvent, cb);

  this->FastBondMapper->AddObserver(vtkCommand::StartEvent, cb);
  this->FastBondMapper->AddObserver(vtkCommand::EndEvent, cb);
  this->FastBondMapper->AddObserver(vtkCommand::ProgressEvent, cb);

  // Connect the trivial producers to forward the glyph polydata
  this->FastAtomMapper->SetInputConnection(this->AtomGlyphPointOutput->GetOutputPort());
  this->FastBondMapper->SetInputConnection(this->BondGlyphPointOutput->GetOutputPort());
}

//----------------------------------------------------------------------------
void MoleculeMapperOpenGL::Render(vtkRenderer *ren, vtkActor *act)
{
  // Update cached polydata if needed
  this->UpdateGlyphPolyData();

  // Pass rendering call on
  // if (this->GetStyle().HasToRenderAtoms())
  {
    this->FastAtomMapper->Render(ren, act);

    if (this->GetStyle().HasToRenderBonds())
    {
      this->FastBondMapper->Render(ren, act);
    }
  }
  if (this->RenderLattice)
  {
    this->LatticeMapper->Render(ren, act);
  }
}

void MoleculeMapperOpenGL::ProcessSelectorPixelBuffers(vtkHardwareSelector *sel,
 std::vector<unsigned int> &pixeloffsets, vtkProp *prop)
{
  // forward to helper
  // if (this->GetStyle().HasToRenderAtoms())
  {
    this->FastAtomMapper->ProcessSelectorPixelBuffers(sel, pixeloffsets, prop);

    if (this->GetStyle().HasToRenderBonds())
    {
      this->FastBondMapper->ProcessSelectorPixelBuffers(sel, pixeloffsets, prop);
    }
  }
  if (this->RenderLattice)
  {
    this->LatticeMapper->ProcessSelectorPixelBuffers(sel, pixeloffsets, prop);
  }
}

//----------------------------------------------------------------------------
void MoleculeMapperOpenGL::ReleaseGraphicsResources(vtkWindow *w)
{
  this->FastAtomMapper->ReleaseGraphicsResources(w);
  this->FastBondMapper->ReleaseGraphicsResources(w);
  this->Superclass::ReleaseGraphicsResources(w);
}

//----------------------------------------------------------------------------
// Generate scale and position information for each atom sphere
void MoleculeMapperOpenGL::UpdateAtomGlyphPolyData()
{
  this->Superclass::UpdateAtomGlyphPolyData();
  this->FastAtomMapper->SetLookupTable(this->GetAtomMapper()->GetLookupTable());
  this->FastAtomMapper->SetScaleArray("Scale Factors");

  // Copy the color array info:
  this->FastAtomMapper->SelectColorArray(this->GetAtomMapper()->GetArrayId());
}

//----------------------------------------------------------------------------
// Generate position, scale, and orientation vectors for each bond cylinder
void MoleculeMapperOpenGL::UpdateBondGlyphPolyData()
{
  this->Superclass::UpdateBondGlyphPolyData();

  switch (this->GetStyle().GetTypeBondsColor())
  {
  case (MMStyle::SingleColor):
    this->FastBondMapper->SetColorModeToDefault();
    this->FastBondMapper->SetScalarModeToUsePointData();
    break;
  default:
  case (MMStyle::DiscreteByAtom):
    this->FastBondMapper->SetLookupTable(
        this->GetBondMapper()->GetLookupTable());
    this->FastBondMapper->SetScalarRange(0, this->PeriodicTable->GetNumberOfElements());
    this->FastBondMapper->SetScalarModeToUsePointData();
    break;
  }

  // Setup glypher
  this->FastBondMapper->SetScaleArray("Scale Factors");
  this->FastBondMapper->SetOrientationArray("Orientation Vectors");
  this->FastBondMapper->SetSelectionIdArray("Selection Ids");
}
