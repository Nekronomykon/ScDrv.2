/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileQTAIM.cpp

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notice for more information.

  =========================================================================*/

#include "MoleculeAcquireFileQTAIM.h"
#include "TraitsAcquireAtoms.h"
#include "CriticalPoints.h"

#include <vtkObjectFactory.h>
#include <vtkExecutive.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;
using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileQTAIM);

//----------------------------------------------------------------------------
MoleculeAcquireFileQTAIM::MoleculeAcquireFileQTAIM()
{
  this->SetNumberOfOutputPorts(3);
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileQTAIM::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "Critical points = " << this->GetNumberOfCPs() << ": ["
     // << (this->HasFileName() ? this->GetFileName() : "(null)" )
     << " ]" << std::endl;
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileQTAIM::Initialize()
{
  // this->Superclass::Initialize();
  this->ResetNumberOfCPs();
  this->ResetNumberOfOrbitals();
  this->ResetNumberOfPrimitives();
}

//----------------------------------------------------------------------------
vtkIdType MoleculeAcquireFileQTAIM::ReadNumberCPs(istream &inss)
{
  vtkIdType nRes = 0;
  istringstream in_str(TraitsBase::ScrollDownToPrefix(inss,
                                                      "Total number of electron density critical points found =",
                                                      57));
  in_str >> nRes;
  assert(!this->GetNumberOfCPs());
  if (nRes)
  {
    this->ResetNumberOfCPs(nRes);
  }
  return nRes;
}

int MoleculeAcquireFileQTAIM::ReadCriticalPoints(istream &inp, CriticalPoints *pCP)
{
  return 1;
}

int MoleculeAcquireFileQTAIM::ParseStreamData(std::istream &src, vtkInformationVector *out)
{
  if (!_Base::ParseStreamData(src, out))
    return 0;

  CriticalPoints *pCP = CriticalPoints::SafeDownCast(vtkDataObject::GetData(out, PortCritical));
  if (!pCP)
  {
    vtkErrorMacro(<< "No CriticalPoints as output for " << this->GetFileName() << " -- skipping");
    return 1;
  }

  return ReadCriticalPoints(src, pCP);
}

CriticalPoints *MoleculeAcquireFileQTAIM::GetOutput()
{
  return this->GetOutput(PortCritical);
}

CriticalPoints *MoleculeAcquireFileQTAIM::GetOutput(int port)
{
  return CriticalPoints::SafeDownCast(this->GetInput(port));
}

void MoleculeAcquireFileQTAIM::SetOutputCritical(CriticalPoints *pCP, bool bUpdate)
{
  this->GetExecutive()->SetOutputData(PortCritical, pCP);
  if (bUpdate && pCP)
    this->SetOutput(pCP->GetMolecule());
}