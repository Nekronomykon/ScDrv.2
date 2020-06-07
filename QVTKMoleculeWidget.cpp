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
    : BaseWidget(parent)
    , renderer_(OpenGLRenderer::New())
    , mapMolecule_(MolMapperOpenGL::New())
    , pickSelect_(RenderedAreaPicker::New())
    , styleInteractor_(IntStyleRbrBndPick::New())
    , mapDataAtoms_(MapLabelAtoms::New())
{
  // VTK Renderer setup
  // renderer_->SetUseFXAA(true); // antaliasing is now On

  Actor mol(OpenGLActor::New());
  mol->SetMapper(mapMolecule_.Get());

  renderer_->AddActor(mol);

  // VTK/Qt wedding...
  vtkRenderWindow *pWnd;
  pWnd = this->renderWindow();
  assert(pWnd);

  vtkRenderWindowInteractor *pIren;
  pIren = this->interactor();
  // pWnd->SetMultiSamples(7);
  pWnd->AddRenderer(renderer_);

  assert(pIren);
  pIren->SetInteractorStyle(styleInteractor_);
  pIren->SetPicker(pickSelect_);

  cmdPickFragment_->ResetMoleculeMapper(mapMolecule_.Get());
  cmdPickFragment_->ResetRenderer(renderer_.Get());
  cmdPickFragment_->ResetAreaPicker(pickSelect_.Get());
  pickSelect_->AddObserver(vtkCommand::EndPickEvent, cmdPickFragment_);

  vtkTextProperty *pTP = mapDataAtoms_->GetLabelTextProperty();
  pTP->SetFontFamilyToCourier();
  pTP->SetColor(0.45, 0.30, 0.45);
  pTP->ShadowOn();
  pTP->BoldOn();
  pTP->SetVerticalJustificationToCentered();
  pTP->SetJustificationToCentered();
  pTP->SetFontSize(16);
  pTP->ItalicOff();

  mapDataAtoms_->SetLabelModeToLabelIds();
  Actor2D lbl(Actor2D::New());
  lbl->SetMapper(mapDataAtoms_);

  renderer_->AddActor2D(lbl);
}

void QVTKMoleculeWidget::ShowMolecule(vtkMolecule *pMol)
{
  mapMolecule_->RemoveAllInputs();
  mapDataAtoms_->RemoveAllInputs();
  if (pMol)
  {
    mapMolecule_->SetInputData(pMol);
    if (mapDataAtoms_)
      mapDataAtoms_->SetInputData(mapMolecule_->AtomGlyphAt());
  }
  // render scene:
  this->doRender();
}

void QVTKMoleculeWidget::doRender()
{
  renderer_->SetBackground(bgColor_.GetData());
  this->renderWindow()->Render();
}

void QVTKMoleculeWidget::ResetMultisample(int idAA)
{
  vtkRenderWindow* pWnd = this->renderWindow();
  pWnd->SetMultiSamples(idAA);
  this->doRender();
}

void QVTKMoleculeWidget::ProjectParallel(bool bPar)
{
  
}
