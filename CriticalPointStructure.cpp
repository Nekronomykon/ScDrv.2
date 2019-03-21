#include "CriticalPointStructure.h"
using namespace vtk;

#include <vtkObject.h>

#include <vtkPoints.h>

// vtkCxxRevisionMacro(CriticalPointStructure, "$Revision: 1.1 $");
//-----------------------------------------------------------------------------
vtkStandardNewMacro(CriticalPointStructure)
// Can not ng here

// CriticalPointStructure::CriticalPointStructure(){}

//-----------------------------------------------------------------------------
void CriticalPointStructure::Initialize()
{
  // molecule_->Initialize();
  this->Superclass::Initialize();
}

//-----------------------------------------------------------------------------
void CriticalPointStructure::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
