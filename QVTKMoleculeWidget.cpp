#include "QVTKMoleculeWidget.h"

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkGenericOpenGLRenderWindow.h>

#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkLODActor.h>

#include <vtkRenderer.h>

#include <vtkNamedColors.h>

#include <vtkPolyDataMapper.h>

typedef vtkSmartPointer<vtkLODActor> LODActor;

QVTKMoleculeWidget::QVTKMoleculeWidget(QWidget* parent)
  : QVTKOpenGLWidget(parent)
  , mol_mapper_(MolMapper::New())
{
  this->setAttribute(Qt::WA_NativeWindow,false);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->SetRenderWindow(renderWindow);

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
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
  Renderer renderer = Renderer::New();

  vtkNew<vtkNamedColors> colrs;
  // renderer->SetBackground(colrs->GetColor3d("Gainsboro").GetData());
  renderer->SetBackground(colrs->GetColor3d("SlateGray").GetData());

  renderer->AddActor(sphereActor);
  renderer->AddActor(mol);

  // VTK/Qt wedded
  this->GetRenderWindow()->AddRenderer(renderer);
}


QVTKMoleculeWidget::~QVTKMoleculeWidget()
{
}
