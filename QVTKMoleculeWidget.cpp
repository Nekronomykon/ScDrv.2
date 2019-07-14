#include "QVTKMoleculeWidget.h"

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkGenericOpenGLRenderWindow.h>

#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkLODActor.h>

#include <vtkPolyData.h>
#include <vtkMolecule.h>

#include <vtkRenderer.h>

#include <vtkOpenGLActor.h>
#include <vtkOpenGLRenderer.h>

// #include <vtkLabelPlacementMapper.h>
#include <vtkLabeledDataMapper.h>

#include <vtkNamedColors.h>
#include <vtkRenderedAreaPicker.h>
#include <vtkPolyDataMapper.h>

#include <vtkTextProperty.h>

#include <vtkInteractorStyleRubberBandPick.h>

#include "MoleculeMapperOpenGL.h"
#include "MapperLabelAtoms.h"
#include "ComboBoxColors.h"

using namespace vtk;

typedef vtkSmartPointer<vtkLODActor> LODActor;
typedef vtkSmartPointer<vtkOpenGLActor> OpenGLActor;
typedef vtkSmartPointer<vtkOpenGLRenderer> OpenGLRenderer;
typedef vtkSmartPointer<vtkInteractorStyleRubberBandPick> IntStyleRbrBndPick;

typedef vtkSmartPointer<MapperLabelAtoms> MapLabelAtoms;

typedef vtkSmartPointer<MoleculeMapperOpenGL> MolMapperOpenGL;
typedef vtkSmartPointer<vtkRenderedAreaPicker> RenderedAreaPicker;

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
    : BaseWidget(parent), renderer_(OpenGLRenderer::New()), mol_mapper_(MolMapperOpenGL::New())
    , area_picker_(RenderedAreaPicker::New()), styleInteractor_(IntStyleRbrBndPick::New())
    , mapDataAtoms_(MapLabelAtoms::New())
{
  // VTK Renderer setup
  // renderer_->SetUseFXAA(true); // antaliasing is now On

  Actor mol(OpenGLActor::New());
  mol->SetMapper(mol_mapper_.Get());

  renderer_->AddActor(mol);

  // VTK/Qt wedding...
  vtkRenderWindow *pWnd;
  vtkRenderWindowInteractor *pIren;
#if (VTK_MAJOR_VERSION >= 8 && VTK_MINOR_VERSION > 2)
  pWnd = this->renderWindow();
  pIren = this->interactor();
#else
  pWnd = this->GetRenderWindow();
  pIren = this->GetInteractor();
#endif
  assert(pWnd);
  // pWnd->SetMultiSamples(7);
  pWnd->AddRenderer(renderer_);

  assert(pIren);
  pIren->SetInteractorStyle(styleInteractor_);
  pIren->SetPicker(area_picker_);

  cmdPickFragment_->ResetMoleculeMapper(mol_mapper_.Get());
  cmdPickFragment_->ResetRenderer(renderer_.Get());
  cmdPickFragment_->ResetAreaPicker(area_picker_.Get());
  area_picker_->AddObserver(vtkCommand::EndPickEvent, cmdPickFragment_);

  vtkTextProperty *pTP = mapDataAtoms_->GetLabelTextProperty();
  pTP->SetFontFamilyToCourier();
  pTP->SetColor(0, 0, 1);
  pTP->ShadowOn();
  pTP->BoldOn();
  pTP->SetVerticalJustificationToCentered();
  pTP->SetJustificationToCentered();
  pTP->SetFontSize(16);
  pTP->ItalicOff();

  // mapDataAtoms_->SetLabelModeToLabelFieldData();
  mapDataAtoms_->SetLabelModeToLabelIds();
  Actor2D lbl(Actor2D::New());
  lbl->SetMapper(mapDataAtoms_);

  renderer_->AddActor2D(lbl);
}

void QVTKMoleculeWidget::ShowMolecule(vtkMolecule *pMol)
{
  mol_mapper_->RemoveAllInputs();
  mapDataAtoms_->RemoveAllInputs();
  if (pMol)
  {
    mol_mapper_->SetInputData(pMol);
    // mol_mapper_->UpdateAtomGlyphPolyData();
    if(mapDataAtoms_)
    mapDataAtoms_->SetInputData(mol_mapper_->AtomGlyphAt());
  }
  // render scene:
  this->doRender();
}

void QVTKMoleculeWidget::doRender()
{
  renderer_->SetBackground(bgColor_.GetData());
#if (VTK_MAJOR_VERSION >= 8 && VTK_MINOR_VERSION > 2)
  this->renderWindow()->Render();
#else
  this->GetRenderWindow()->Render();
#endif
}
