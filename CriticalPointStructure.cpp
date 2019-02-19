#include "CriticalPointStructure.h"
using namespace vtk;

#include <vtkPoints.h>

void CriticalPointStructure::Initialize()
{
  points_->Initialize();
  this->Superclass::Initialize();
}

void CriticalPointStructure::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}