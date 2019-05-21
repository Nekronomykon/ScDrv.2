#include "CriticalPoints.h"
using namespace vtk;

#include <vtkObject.h>

#include <vtkPoints.h>

// vtkCxxRevisionMacro(CriticalPoints, "$Revision: 1.1 $");
//-----------------------------------------------------------------------------
vtkStandardNewMacro(CriticalPoints)

// CriticalPoints::CriticalPoints(){}

//-----------------------------------------------------------------------------
void CriticalPoints::Initialize()
{
  // molecule_->Initialize();
  this->Superclass::Initialize();
}

//-----------------------------------------------------------------------------
void CriticalPoints::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
