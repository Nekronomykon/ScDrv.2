#include "QVTKMoleculeWidget.h"

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkGenericOpenGLRenderWindow.h>

#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkLODActor.h>

#include <vtkMolecule.h>

#include <vtkRenderer.h>

#include <vtkOpenGLActor.h>
#include <vtkOpenGLRenderer.h>

#include <vtkLabelPlacementMapper.h>

#include <vtkNamedColors.h>
#include <vtkRenderedAreaPicker.h>
#include <vtkPolyDataMapper.h>

#include <vtkInteractorStyleRubberBandPick.h>

#include "MoleculeMapperOpenGL.h"
#include "ComboBoxColors.h"

using namespace vtk;

typedef vtkSmartPointer<vtkLODActor> LODActor;
typedef vtkSmartPointer<vtkOpenGLActor> OpenGLActor;
typedef vtkSmartPointer<vtkOpenGLRenderer> OpenGLRenderer;
typedef vtkSmartPointer<vtkInteractorStyleRubberBandPick> IntStyleRbrBndPick;

typedef vtkSmartPointer<MoleculeMapperOpenGL> MolMapperOpenGL;
typedef vtkSmartPointer<vtkRenderedAreaPicker> RenderedAreaPicker;

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
    : BaseWidget(parent)
    , renderer_(OpenGLRenderer::New())
    , mol_mapper_(MolMapperOpenGL::New())
    , area_picker_(RenderedAreaPicker::New())
    , styleInteractor_(IntStyleRbrBndPick::New())
{
  // VTK Renderer setup
  // renderer_->SetUseFXAA(true); // antaliasing is now On

  Actor mol(OpenGLActor::New());
  mol->SetMapper(mol_mapper_.Get());

  renderer_->AddActor(mol);

  // VTK/Qt wedding...
  this->renderWindow()->AddRenderer(renderer_);

  vtkRenderWindowInteractor *pIren = this->interactor();
  assert(pIren);
  pIren->SetInteractorStyle(styleInteractor_);
  pIren->SetPicker(area_picker_);

  cmdPickFragment_->ResetMoleculeMapper(mol_mapper_.Get());
  cmdPickFragment_->ResetRenderer(renderer_.Get());
  cmdPickFragment_->ResetAreaPicker(area_picker_.Get());
  area_picker_->AddObserver(vtkCommand::EndPickEvent, cmdPickFragment_);
}

void QVTKMoleculeWidget::ShowMolecule(vtkMolecule *pMol)
{
  mol_mapper_->RemoveAllInputs();
  if (pMol)
  {
    mol_mapper_->SetInputData(pMol);
  }

  // render scene:
  this->doRender();
}

void QVTKMoleculeWidget::doRender()
{
  renderer_->SetBackground(bgColor_.GetData());
  this->renderWindow()->Render();
}
