/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module : MoleculeAcquireFileARC.cxx

  Copyright(c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.See the above copyright notice for more information.

  ======================================================================== = */

#include "MoleculeAcquireFileARC.h"

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
vtkStandardNewMacro(MoleculeAcquireFileARC);

MoleculeAcquireFileARC::MoleculeAcquireFileARC() : MoleculeAcquireFile() {}

MoleculeAcquireFileARC::~MoleculeAcquireFileARC() {}

//----------------------------------------------------------------------------
void MoleculeAcquireFileARC::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}


int MoleculeAcquireFileARC::RequestInformation(vtkInformation *vtkNotUsed(request),
                                               vtkInformationVector **vtkNotUsed(inputVector),
                                               vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  if (!this->HasFileName())
    return 0;

  std::ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileARC error opening file: " << this->FileName());
    return 0;
  }

  int natoms = 0;
  // istream::pos_type current_pos = file_in.tellg();
  std::string str_line;
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileARC: unexpected EOF at " << this->FileName());
    return 0;
  }
  do
  {
    if (!file_in)
    {
      vtkErrorMacro(<< "MoleculeAcquireFileARC: unexpected EOF at " << this->FileName());
      return 0;
    }
    if (str_line.find("FINAL GEOMETRY OBTAINED") != std::string::npos)
      break;
  } while (std::getline(file_in, str_line));

  do
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro(<< "MoleculeAcquireFileARC: unexpected EOF at " << this->FileName());
      return 0;
    }

  } while (!str_line.empty());

  assert(!this->GetNumberOfAtoms()); // assured that it is read first
  natoms = Traits::MeasureStringGroup(file_in);
  this->SetNumberOfAtoms(natoms);

  return 1;
}

int MoleculeAcquireFileARC::RequestData(vtkInformation *,
                                        vtkInformationVector **,
                                        vtkInformationVector *outVector)
{
  vtkInformation *outInfo = outVector->GetInformationObject(0);

  vtkMolecule *output = vtkMolecule::SafeDownCast(vtkDataObject::GetData(outVector));

  if (!output)
  {
    vtkErrorMacro(<< "MoleculeAcquireFileARC does not have a vtkMolecule as output.");
    return 1;
  }

  if (!this->HasFileName())
    return 0;

  ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileARC error opening file: " << this->FileName());
    return 0;
  }

  std::string str_line;
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileARC: unexpected EOF at " << this->FileName());
    return 0;
  }
  do
  {
    if (!file_in)
    {
      vtkErrorMacro(<< "MoleculeAcquireFileARC: unexpected EOF at " << this->FileName());
      return 0;
    }
    if (str_line.find("FINAL GEOMETRY OBTAINED") != std::string::npos)
      break;
  } while (std::getline(file_in, str_line));

  std::getline(file_in, str_line);
  std::getline(file_in, str_line);
  std::getline(file_in, str_line);

  // construct vtkMolecule
  int nResult = Traits::AppendAtoms(file_in, this->GetNumberOfAtoms(), output);
  if (nResult)
  {
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading atom #" << nResult
        << " from " << this->FileName()
        << " Premature EOF while reading molecule."
      );
    if (nResult < 0)
      vtkErrorMacro(<< "MoleculeAcquireFileXYZ error parsing atom #" << -nResult
        << " from " << this->FileName()
        << " Premature EOF while reading molecule."
      );
    return 0;
  }
  return 1;
}

