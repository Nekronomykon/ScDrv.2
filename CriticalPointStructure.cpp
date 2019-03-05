#include "CriticalPointStructure.h"
using namespace vtk;

#include <vtkPoints.h>

//-----------------------------------------------------------------------------
vtkObjectFactoryNewMacro(CriticalPointStructure)
// Can not yet understand what is wrong here

//-----------------------------------------------------------------------------
void CriticalPointStructure::Initialize()
{
  points_->Initialize();
  this->Superclass::Initialize();
}

//-----------------------------------------------------------------------------
void CriticalPointStructure::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
