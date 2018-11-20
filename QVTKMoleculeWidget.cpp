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
#include <vtkOpenGLMoleculeMapper.h>

#include <vtkNamedColors.h>

#include <vtkPolyDataMapper.h>

#include <vtkInteractorStyleRubberBandPick.h>

typedef vtkSmartPointer<vtkLODActor> LODActor;
typedef vtkSmartPointer<vtkOpenGLActor> OpenGLActor;
typedef vtkSmartPointer<vtkOpenGLRenderer> OpenGLRenderer;
typedef vtkSmartPointer<vtkOpenGLMoleculeMapper> OpenGLMolMapper;

typedef vtkSmartPointer<vtkInteractorStyleRubberBandPick> IntStyleRbrBndPick;

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_Sticks =
{ true, vtkMoleculeMapper::UnitRadius, 0.15f, true, false, vtkMoleculeMapper::DiscreteByAtom, 0.15f };
// [0] -> sticks

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_BnS =
{ true, vtkMoleculeMapper::VDWRadius, 0.25f, true, false, vtkMoleculeMapper::DiscreteByAtom, 0.125f };
// [1] -> balls and sticks

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_VdW =
{ true, vtkMoleculeMapper::VDWRadius, 1.0f, false, false, 0, 0 };
// [2] -> van der Waals

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_Fast =
{ true, vtkMoleculeMapper::UnitRadius, 0.375f, true, false, vtkMoleculeMapper::SingleColor, 0.1f };
// [3] -> fast internal

QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleFast() { return style_Fast; }
QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleFill() { return style_VdW; }
QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleBall() { return style_BnS; }
QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleBond() { return style_Sticks; }

vtkStdString QVTKMoleculeWidget::name_default_background("antique_white");

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
  : BaseWidget(parent), renderer_(OpenGLRenderer::New())
  , name_background_(GetDefaultBackgroundColorName())
  , mol_mapper_(OpenGLMolMapper::New()), mol_style_(style_Fast)
  , styleInteractor_(IntStyleRbrBndPick::New())
{
  // this->setAttribute(Qt::WA_NativeWindow, false);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->SetRenderWindow(renderWindow);

  // Molecule actor
  Actor mol(OpenGLActor::New());
  mol->SetMapper(mol_mapper_.Get());

  // VTK Renderer
  renderer_->SetUseFXAA(true); // antaliasing is now On

  this->AdjustBackgroundColor();
  // renderer->AddActor(sphereActor);
  renderer_->AddActor(mol);

  // VTK/Qt wedded
  this->GetRenderWindow()->AddRenderer(renderer_);

  vtkRenderWindowInteractor* pIren = this->GetInteractor();
  assert(pIren);
  pIren->SetInteractorStyle(styleInteractor_);

  pIren->AddObserver(vtkCommand::EndPickEvent, cmdPickFragment_);
}

QVTKMoleculeWidget::~QVTKMoleculeWidget() {}

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

bool QVTKMoleculeWidget::resetStyle(const QVTKMoleculeMapStyle &style)
{
  if (style == mol_style_)
    return false;
  mol_style_ = style;
  this->doRender();
  return true;
}

void QVTKMoleculeWidget::doRender()
{
  renderer_->SetBackground(bgColor_.GetData());
  mol_style_.SetupMoleculeMapper(mol_mapper_);
  this->GetRenderWindow()->Render();
}

vtkStdString QVTKMoleculeWidget::GetDefaultBackgroundColorName() { return name_default_background; }

vtkStdString QVTKMoleculeWidget::ResetDefaultBackgroundColorName(vtkStdString name_new)
{
  std::swap(name_default_background, name_new);
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


bool QVTKMoleculeWidget::moleculeInBallsSticks() const { return bool(mol_style_ == style_BnS); }

bool QVTKMoleculeWidget::moleculeInSpaceFill() const { return bool(mol_style_ == style_VdW); }

bool QVTKMoleculeWidget::moleculeInFastRender() const { return bool(mol_style_ == style_Fast); }

bool QVTKMoleculeWidget::moleculeInSticks() const { return bool(mol_style_ == style_Sticks); }
