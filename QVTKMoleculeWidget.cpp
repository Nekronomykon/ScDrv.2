#include "QVTKMoleculeWidget.h"

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkGenericOpenGLRenderWindow.h>

#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkLODActor.h>

#include <vtkMolecule.h>

#include <vtkRenderer.h>

#include <vtkOpenGLRenderer.h>
#include <vtkOpenGLMoleculeMapper.h>

#include <vtkNamedColors.h>

#include <vtkPolyDataMapper.h>

typedef vtkSmartPointer<vtkLODActor> LODActor;

typedef vtkSmartPointer<vtkOpenGLRenderer> OpenGLRenderer;
typedef vtkSmartPointer<vtkOpenGLMoleculeMapper> OpenGLMolMapper;

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_Sticks =
    {true, vtkMoleculeMapper::UnitRadius, 0.15f, true, false, vtkMoleculeMapper::DiscreteByAtom, 0.15f};
// [0] -> sticks

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_BnS =
    {true, vtkMoleculeMapper::VDWRadius, 0.25f, true, false, vtkMoleculeMapper::DiscreteByAtom, 0.125f};
// [1] -> balls and sticks

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_VdW =
    {true, vtkMoleculeMapper::VDWRadius, 1.0f, false, false, 0, 0};
// [2] -> van der Waals

const QVTKMoleculeMapStyle QVTKMoleculeWidget::style_Fast =
    {true, vtkMoleculeMapper::UnitRadius, 0.375f, true, false, vtkMoleculeMapper::SingleColor, 0.1f};
// [3] -> fast internal

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
    : QVTKOpenGLWidget(parent), mol_mapper_(OpenGLMolMapper::New()), mol_style_(style_Fast)
{
  // this->setAttribute(Qt::WA_NativeWindow, false);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->SetRenderWindow(renderWindow);

  // Molecule actor
  LODActor mol = LODActor::New();
  mol->SetMapper(mol_mapper_.Get());

  // VTK Renderer
  Renderer renderer(OpenGLRenderer::New());

  vtkNew<vtkNamedColors> colrs;
  // renderer->SetBackground(colrs->GetColor3d("Gainsboro").GetData());
  renderer->SetBackground(colrs->GetColor3d("SlateGray").GetData());

  // renderer->AddActor(sphereActor);
  renderer->AddActor(mol);

  // VTK/Qt wedded
  this->GetRenderWindow()->AddRenderer(renderer);
}

QVTKMoleculeWidget::~QVTKMoleculeWidget() {}

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
  if(style == mol_style_)
    return false;
  mol_style_ = style;
  this->doRender();
  return true;
}

void QVTKMoleculeWidget::doRender()
{
  mol_style_.SetupMoleculeMapper(mol_mapper_);
  this->GetRenderWindow()->Render();
}

bool QVTKMoleculeWidget::moleculeInBallsSticks() const {return bool (mol_style_ == style_BnS);}

bool QVTKMoleculeWidget::moleculeInSpaceFill() const   {return bool (mol_style_ == style_VdW);}

bool QVTKMoleculeWidget::moleculeInFastRender() const  {return bool (mol_style_ == style_Fast);}

bool QVTKMoleculeWidget::moleculeInSticks() const {return bool (mol_style_ == style_Sticks);}
