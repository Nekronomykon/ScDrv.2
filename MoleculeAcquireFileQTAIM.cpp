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
#include <vtkStdString.h>

#include <vtkPoints.h>

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
    : MoleculeAcquireFileField(3)
{
  CriticalPoints *pCP;
  pCP = CriticalPoints::New();
  pCP->ReleaseData();
  this->GetExecutive()->SetOutputData(PortCritical, pCP);
  pCP->Delete();
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

int MoleculeAcquireFileQTAIM::ReadCritical(istream &inp, CriticalPoints *pCP)
{
  string strNewCP = TraitsBase::ScrollDownToPrefix(inp, "CP#");
  if (strNewCP.empty())
    return 0;

  double x, y, z;
  vtkStdString skip, line_one;
  char c_skip;

  pCP->Points()->Resize(this->GetNumberOfCPs());

  do // by idCP
  {
    istringstream iss(strNewCP);
    /* code */
    size_t idCP = 0;
    iss >> idCP >> skip >> c_skip >> x >> y >> z; // Coords in Bohrs
    if (!idCP)
      return 0;
    --idCP; // now it is the index
    if (c_skip = '=')
      pCP->Points()->SetPoint(idCP, x, y, z);

      /* next line: */
    getline(inp, line_one);

    /* finally: */
    strNewCP = TraitsBase::ScrollDownToPrefix(inp, "CP#");
  } while (!strNewCP.empty());

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

  return this->ReadCritical(src, pCP);
}

CriticalPoints *MoleculeAcquireFileQTAIM::GetCriticalOutput()
{
  return this->GetCriticalOutputAt(PortCritical);
}

CriticalPoints *MoleculeAcquireFileQTAIM::GetCriticalOutputAt(int port)
{
  return CriticalPoints::SafeDownCast(this->GetInput(port));
}

void MoleculeAcquireFileQTAIM::SetCriticalOutput(CriticalPoints *pCP, bool bUpdate)
{
  this->GetExecutive()->SetOutputData(PortCritical, pCP);
  if (bUpdate && pCP)
    this->SetOutput(pCP->GetMolecule());
}

int MoleculeAcquireFileQTAIM::FillOutputPortInformation(int port, vtkInformation *info)
{
  if (port == PortMolecule || port == PortGrid)
    return this->Superclass::FillOutputPortInformation(port, info);

  info->Set(vtkDataObject::DATA_TYPE_NAME(), "CriticalPoints");
  return 1;
}
