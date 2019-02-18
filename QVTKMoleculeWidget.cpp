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

using namespace vtk;

typedef vtkSmartPointer<vtkLODActor> LODActor;
typedef vtkSmartPointer<vtkOpenGLActor> OpenGLActor;
typedef vtkSmartPointer<vtkOpenGLRenderer> OpenGLRenderer;
typedef vtkSmartPointer<vtkInteractorStyleRubberBandPick> IntStyleRbrBndPick;

typedef vtkSmartPointer<MoleculeMapperOpenGL> MolMapperOpenGL;
typedef vtkSmartPointer<vtkRenderedAreaPicker> RenderedAreaPicker;



vtkStdString QVTKMoleculeWidget::name_background_default("antique_white");

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
  : BaseWidget(parent), renderer_(OpenGLRenderer::New())
  , name_background_(GetDefaultBackgroundColorName())
  , mol_mapper_(MolMapperOpenGL::New())
  , area_picker_(RenderedAreaPicker::New())
  , styleInteractor_(IntStyleRbrBndPick::New())
{
  // this->setAttribute(Qt::WA_NativeWindow, false);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->SetRenderWindow(renderWindow);

  // Molecule actor
  Actor mol(OpenGLActor::New());
  mol->SetMapper(mol_mapper_.Get());

  // VTK Renderer setup
  renderer_->SetUseFXAA(true); // antaliasing is now On

  this->AdjustBackgroundColor();
  renderer_->AddActor(mol);

  // VTK/Qt wedding...
  this->GetRenderWindow()->AddRenderer(renderer_);

  vtkRenderWindowInteractor* pIren = this->GetInteractor();
  assert(pIren);
  pIren->SetInteractorStyle(styleInteractor_);
  pIren->SetPicker(area_picker_);

  cmdPickFragment_->ResetMoleculeMapper(mol_mapper_.Get());
  cmdPickFragment_->ResetRenderer(renderer_.Get());
  cmdPickFragment_->ResetAreaPicker(area_picker_.Get());
  area_picker_->AddObserver(vtkCommand::EndPickEvent, cmdPickFragment_);
}

void QVTKMoleculeWidget::AdjustBackgroundColor()
{
  vtkNew<vtkNamedColors> colors;
  bgColor_ = colors->GetColor3d(name_background_);

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
  this->GetRenderWindow()->Render();
  // this->GetMoleculeMapper()->Render();
  // renderer_->Render();
}

vtkStdString QVTKMoleculeWidget::GetDefaultBackgroundColorName() { return name_background_default; }

vtkStdString QVTKMoleculeWidget::ResetDefaultBackgroundColorName(vtkStdString name_new)
{
  std::swap(name_background_default, name_new);
  return name_new;
}

vtkStdString QVTKMoleculeWidget::GetBackgroundColorName() const { return name_background_; }
vtkStdString QVTKMoleculeWidget::ResetBackgroundColorName(vtkStdString name_new)
{
  std::swap(name_background_, name_new);
  this->AdjustBackgroundColor();
  this->doRender();
  return name_new;
}
