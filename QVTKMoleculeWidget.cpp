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

#include <vtkNamedColors.h>
#include <vtkRenderedAreaPicker.h>
#include <vtkPolyDataMapper.h>

#include <vtkInteractorStyleRubberBandPick.h>

#include "MoleculeMapperOpenGL.h"

typedef vtkSmartPointer<vtkLODActor> LODActor;
typedef vtkSmartPointer<vtkOpenGLActor> OpenGLActor;
typedef vtkSmartPointer<vtkOpenGLRenderer> OpenGLRenderer;
typedef vtkSmartPointer<vtkInteractorStyleRubberBandPick> IntStyleRbrBndPick;

typedef vtkSmartPointer<MoleculeMapperOpenGL> MolMapperOpenGL;
typedef vtkSmartPointer<vtkRenderedAreaPicker> RenderedAreaPicker;


const MoleculeMapperStyle QVTKMoleculeWidget::style_Sticks =
{ true, MoleculeMapper::UnitRadius, 0.15f, true, false, MoleculeMapper::DiscreteByAtom, 0.15f };
// [0] -> sticks

const MoleculeMapperStyle QVTKMoleculeWidget::style_BnS =
{ true, MoleculeMapper::VDWRadius, 0.25f, true, false, MoleculeMapper::DiscreteByAtom, 0.125f };
// [1] -> balls and sticks

const MoleculeMapperStyle QVTKMoleculeWidget::style_VdW =
{ true, MoleculeMapper::VDWRadius, 1.0f, false, false, 0, 0 };
// [2] -> van der Waals

const MoleculeMapperStyle QVTKMoleculeWidget::style_Fast =
{ true, MoleculeMapper::UnitRadius, 0.375f, true, false, MoleculeMapper::SingleColor, 0.1f, 64, 64, 64};
// [3] -> fast internal

QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleFast() { return style_Fast; }
QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleFill() { return style_VdW; }
QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleBall() { return style_BnS; }
QVTKMoleculeWidget::MolStyle QVTKMoleculeWidget::styleBond() { return style_Sticks; }

vtkStdString QVTKMoleculeWidget::name_background_default("antique_white");

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
  : BaseWidget(parent), renderer_(OpenGLRenderer::New())
  , name_background_(GetDefaultBackgroundColorName())
  , mol_mapper_(MolMapperOpenGL::New()), mol_style_(style_Fast)
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

bool QVTKMoleculeWidget::resetStyle(const MoleculeMapperStyle &style)
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


bool QVTKMoleculeWidget::moleculeInBallsSticks() const { return bool(mol_style_ == style_BnS); }

bool QVTKMoleculeWidget::moleculeInSpaceFill() const { return bool(mol_style_ == style_VdW); }

bool QVTKMoleculeWidget::moleculeInFastRender() const { return bool(mol_style_ == style_Fast); }

bool QVTKMoleculeWidget::moleculeInSticks() const { return bool(mol_style_ == style_Sticks); }
