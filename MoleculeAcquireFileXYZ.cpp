/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileXYZ.cxx

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "MoleculeAcquireFileXYZ.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>

#include <vtkMolecule.h>
#include <vtkPeriodicTable.h>

#include <vtkStreamingDemandDrivenPipeline.h>

#include <cmath>
#include <cstring>

#include <fstream>
#include <sstream>

#include "TraitsAcquireAtoms.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileXYZ);

//----------------------------------------------------------------------------
MoleculeAcquireFileXYZ::MoleculeAcquireFileXYZ()
{}

//----------------------------------------------------------------------------
MoleculeAcquireFileXYZ::~MoleculeAcquireFileXYZ()
{}

//----------------------------------------------------------------------------
//vtkMolecule *MoleculeAcquireFileXYZ::GetOutput()
//{
//  return vtkMolecule::SafeDownCast(this->GetOutputDataObject(0));
//}

//----------------------------------------------------------------------------
//void MoleculeAcquireFileXYZ::SetOutput(vtkMolecule *output)
//{
//  this->GetExecutive()->SetOutputData(0, output);
//}

int MoleculeAcquireFileXYZ::RequestInformation(vtkInformation *vtkNotUsed(request)
  , vtkInformationVector **vtkNotUsed(inputVector)
  , vtkInformationVector *outputVector)
{
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  if (!this->HasFileName())
    return 0;

  std::ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error opening file: " << this->FileName());
    return 0;
  }

  int natoms = 0;
  // istream::pos_type current_pos = file_in.tellg();
  std::string str_line;
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading number of atoms:" << this->FileName());
    return 0;
  }
  std::istringstream ssinp(str_line);
  ssinp >> natoms;

  assert(!this->GetNumberOfAtoms()); // assured that it is read first
  this->SetNumberOfAtoms(natoms);

  std::string title;
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading title string: " << this->FileName());
    return 0;
  }

  int nStrings = Traits::MeasureStringGroup(file_in);

  return (nStrings >= natoms) ? 1 : 0;
}

int MoleculeAcquireFileXYZ::RequestData(vtkInformation *,
  vtkInformationVector **,
  vtkInformationVector *outVector)
{
  vtkInformation* outInfo = outVector->GetInformationObject(0);

  vtkMolecule *output = vtkMolecule::SafeDownCast(vtkDataObject::GetData(outVector));

  if (!output)
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ does not have a vtkMolecule as output.");
    return 1;
  }

  if (!this->HasFileName())
    return 0;

  ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error opening file: " << this->FileName());
    return 0;
  }

  int timestep = 0;
  int nbAtoms = 0;
  std::string str_line;

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading number of atoms:" << this->FileName());
    return 0;
  }
  std::istringstream ssinp(str_line);
  ssinp >> nbAtoms;
  // file_in.get(); // end of line char

  if (nbAtoms != this->GetNumberOfAtoms())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading atom number " << this->FileName()
      << " Premature EOF while reading molecule.");
    // file_in.close();
    return 0;
  }
  std::string title;
  std::getline(file_in, title);  // second line is a title

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

//----------------------------------------------------------------------------
void MoleculeAcquireFileXYZ::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
