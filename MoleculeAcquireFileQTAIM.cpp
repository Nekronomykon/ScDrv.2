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
#include <complex>

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

  os << indent << "Critical points = " << this->GetCriticalPointNumber() << ": ["
     // << (this->HasFileName() ? this->GetFileName() : "(null)" )
     << " ]" << std::endl;
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileQTAIM::Initialize()
{
  // this->Superclass::Initialize();
  this->ResetCriticalPointNumber();
  this->ResetNumberOfOrbitals();
  this->ResetNumberOfPrimitives();
}

//----------------------------------------------------------------------------
vtkIdType MoleculeAcquireFileQTAIM::ReadCriticalInfo(istream &inss, vtkInformationVector * /* info */)
{
  vtkIdType nRes = 0;
  istringstream in_str(TraitsBase::ScrollDownToPrefix(inss,
                                                      "Total number of electron density critical points found =",
                                                      57));
  in_str >> nRes;
  assert(!this->GetCriticalPointNumber());
  if (nRes)
  {
    this->ResetCriticalPointNumber(nRes);
  }
  return nRes;
}

int MoleculeAcquireFileQTAIM::ReadCriticalData(istream &inp, CriticalPoints *pCP)
{
  string strNewCP = TraitsBase::ScrollDownToPrefix(inp, "CP#");
  if (strNewCP.empty())
    return 0;

  auto *pPts = pCP->Points();
  assert(pPts);

  vtkStdString skip, line_one;
  char c_skip;

  double x, y, z;
  complex<int> code; // for the I/O '(Re,Im)' convenience...

  pPts->Resize(this->GetCriticalPointNumber());

  do // by idCP
  {
    istringstream iss(strNewCP);
    /* code */
    size_t idCP = 0;
    iss >> idCP >> skip >> c_skip >> x >> y >> z; // Coords in Bohrs
    if (!idCP)
      return 0;

    assert(c_skip == '=');
    /* next line: */

    getline(inp, line_one);
    istringstream is_type(line_one);
    is_type >> skip >> c_skip >> code >> skip;

    if (code.real() == 3) // (1) does AIMAll give any other values?
    {                     // (2) what should one do, if any point is degenerate?
    // ..by possible values here is:
      if (code.imag() == -3)      // a local maximum --> atom (skip == "NACP")
      { // or not (skip == "NNACP"). In the first case:
        // read a single number (== index + 1) after in the ElementSymbolNumber format;
        // it is possibly equal to idCP here. 
        // I do not know what to do otherwise ;) 
      }
      else if(code.imag() == -1)  // saddle point of rank 1 --> bond (skip == "BCP"):
      { // read two numbers in the format desribed above for (-3) case; let them be n0 and n1;
        // then add (n0-1,idCP-1) and (n1-1,idCP-1) edges to the critical graph of the structure
      }
      else if(code.imag() == +1)  // saddle point of rank 2 --> ring (skip == "RCP");
      { // read all numbers in the format described above; find all bonds between them 
        // as their indices m_0, m_1 ... m_N;
        // then add all edges of the type (m_i, idCP - 1)
        // NOTA BENE: RCP is not the sign that we have all BCPs at hand --> conversion?
      }
      else if(code.imag() == +3)  // a local mininum --> cage (skip == "CCP")
      { // AIMAll gives all atomic indices after the "CCP" token in the string;
        // TODO: I do not know what to do with them all. To think on about it!
        // NOTA BENE: CCP is not the sign that we have all BCPs and RCPs at hand
        //             --> conversion?
      }
      else return 0; // DOMAIN ERROR!!!
    }
    else if(code.real() == 2)
    { // Actually we have had the result of this type: the ES potential in H--X possess 
      // the axial symmetry of the infinite order, so does the GS electronic density...
      // OUCH!
    }
    else return 0;
    
    // now data are read; let us store them
    --idCP; // now it is the index
    pPts->SetPoint(idCP, x, y, z);

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

  return this->ReadCriticalData(src, pCP);
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
