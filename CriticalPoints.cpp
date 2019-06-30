#include "CriticalPoints.h"
using namespace vtk;

#include <vtkObject.h>
#include <vtkFloatArray.h>
#include <vtkPoints.h>
#include <vtkMolecule.h>


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

//-----------------------------------------------------------------------------
vtkPoints *CriticalPoints::Points() const { return points_; }

//-----------------------------------------------------------------------------
void CriticalPoints::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
