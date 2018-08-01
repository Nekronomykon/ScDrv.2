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

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget *parent)
    : QVTKOpenGLWidget(parent), mol_mapper_(OpenGLMolMapper::New())
{
  this->setAttribute(Qt::WA_NativeWindow, false);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->SetRenderWindow(renderWindow);

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetThetaResolution(14);
  sphereSource->SetPhiResolution(14);
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  Actor sphereActor = Actor::New();
  sphereActor->SetMapper(sphereMapper);

  // Molecule actor
  LODActor mol = LODActor::New();
  mol->SetMapper(mol_mapper_.Get());

  // VTK Renderer
  Renderer renderer(OpenGLRenderer::New());

  vtkNew<vtkNamedColors> colrs;
  // renderer->SetBackground(colrs->GetColor3d("Gainsboro").GetData());
  renderer->SetBackground(colrs->GetColor3d("SlateGray").GetData());

  renderer->AddActor(sphereActor);
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
    mol_mapper_->Update();
  }
  this->GetRenderWindow()->Render();
}