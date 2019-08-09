#include "CriticalPoints.h"
using namespace vtk;

#include <vtkObject.h>
#include <vtkIdTypeArray.h>
#include <vtkFloatArray.h>
#include <vtkPoints.h>
#include <vtkMolecule.h>

// vtkCxxRevisionMacro(CriticalPoints, "$Revision: 1.1 $");
//-----------------------------------------------------------------------------
vtkStandardNewMacro(CriticalPoints);

//-----------------------------------------------------------------------------
void CriticalPoints::Initialize()
{
  // molecule_->Initialize();
  this->Superclass::Initialize();
}

//-----------------------------------------------------------------------------
void CriticalPoints::ResetPointSize(vtkIdType nPoints)
{
  if (nPoints < 0)
    nPoints = 0;
  if (nPoints != this->GetPointSize())
  {
    points_->SetNumberOfPoints(nPoints);
    point_types_->Resize(nPoints);
  }
}

//-----------------------------------------------------------------------------
vtkIdType CriticalPoints::GetPointSize() const
{
  return points_->GetNumberOfPoints();
}

//-----------------------------------------------------------------------------
vtkPoints *CriticalPoints::Points() const { return points_; }

//-----------------------------------------------------------------------------
void CriticalPoints::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//-----------------------------------------------------------------------------
bool CriticalPoints::SetAtomCriticalPointAt(vtkIdType idx, const double *xyz)
{
  if (this->GetPointSize() >= idx)
    return false;
  points_->SetPoint(idx, xyz);
  point_types_->SetValue(idx, AtomMaximumCP);
  return true;
}

//-----------------------------------------------------------------------------
bool CriticalPoints::SetBondCriticalPointAt(vtkIdType idx, const double *xyz)
{
  if (this->GetPointSize() >= idx)
    return false;
  points_->SetPoint(idx, xyz);
  point_types_->SetValue(idx, BondSaddleCP);
  return true;
}

//-----------------------------------------------------------------------------
bool CriticalPoints::SetRingCriticalPointAt(vtkIdType idx, const double *xyz)
{
  if (this->GetPointSize() >= idx)
    return false;
  points_->SetPoint(idx, xyz);
  point_types_->SetValue(idx, RingSaddleCP);
  return true;
}

//-----------------------------------------------------------------------------
bool CriticalPoints::SetCageCriticalPointAt(vtkIdType idx, const double *xyz)
{
  if (this->GetPointSize() >= idx)
    return false;
  points_->SetPoint(idx, xyz);
  point_types_->SetValue(idx, CageMinimumCP);
  return true;
}
