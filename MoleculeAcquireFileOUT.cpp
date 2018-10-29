/*=========================================================================

Program:   Visualization Toolkit Local Copy
  Module : MoleculeAcquireFileOUT.cxx

  Copyright(c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.See the above copyright notice for more information.

  ======================================================================== = */

#include "MoleculeAcquireFileOUT.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>

#include <vtkMolecule.h>
#include <vtkPeriodicTable.h>

#include <vtkStreamingDemandDrivenPipeline.h>

#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileOUT);

//----------------------------------------------------------------------------
MoleculeAcquireFileOUT::MoleculeAcquireFileOUT()
    : MoleculeAcquireFile()
{
}

//----------------------------------------------------------------------------
MoleculeAcquireFileOUT::~MoleculeAcquireFileOUT()
{
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileOUT::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int MoleculeAcquireFileOUT::RequestInformation(vtkInformation *vtkNotUsed(request),
                                               vtkInformationVector **vtkNotUsed(inputVector),
                                               vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  if (!this->HasFileName())
    return 0;

  std::ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileOUT error opening file: " << this->FileName());
    return 0;
  }

  int natoms = 0;
  bool read_str;
  std::string str_line;

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileOUT error reading number of atoms:" << this->FileName());
    return 0;
  }
  do
  {
    if (str_line.size() < 50)
      continue;
    int nCmp = str_line.compare(29, 21, "CARTESIAN COORDINATES");
    if (!nCmp)
    {
      // init scan results:
      natoms = Traits::MeasureStringGroup(file_in);
      assert(natoms > 0);
      this->SetNumberOfAtoms(natoms);
      break;
    }
  } while (std::getline(file_in, str_line));

  return natoms;
}

//----------------------------------------------------------------------------
int MoleculeAcquireFileOUT::RequestData(vtkInformation *vtkNotUsed(request),
                                        vtkInformationVector **vtkNotUsed(inputVector),
                                        vtkInformationVector *outVector)
{
  vtkInformation *outInfo = outVector->GetInformationObject(0);

  vtkMolecule *output = vtkMolecule::SafeDownCast(vtkDataObject::GetData(outVector));

  if (!output)
  {
    vtkErrorMacro(<< "MoleculeAcquireFileOUT does not have a vtkMolecule as output.");
    return 1;
  }

  if (!this->HasFileName())
    return 0;

  ifstream file_in(this->GetFileName());
  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileOUT error opening file: " << this->FileName());
    return 0;
  }

  int timestep = 0;
  int nbAtoms = 0;
  std::string str_line;

  int natoms = 0;
  int nResult = -1;
  bool read_str;

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileOUT error: premature EOF in " << this->FileName());
    return 0;
  }
  do
  {
    if (str_line.size() < 50)
      continue;
    int nCmp = str_line.compare(29, 21, "CARTESIAN COORDINATES");
    if (!nCmp)
    {
      if (!std::getline(file_in, str_line))
      {
        vtkErrorMacro(<< "MoleculeAcquireFileOUT error: premature EOF in " << this->FileName());
        return 0;
      }

      // init scan results:
      nResult = AppendAtoms(file_in, this->GetNumberOfAtoms(), output);
      if (nResult)
      {
        if (nResult > 0)
          vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading atom #" << nResult
                        << " from " << this->FileName()
                        << " Premature EOF while reading molecule.");
        if (nResult > 0)
          vtkErrorMacro(<< "MoleculeAcquireFileXYZ error parsing atom #" << -nResult
                        << " from " << this->FileName()
                        << " Premature EOF while reading molecule.");
        return 0;
      }
      break;
    }
  } while (std::getline(file_in, str_line));
  return (nResult) ? 0 : 1;
}
