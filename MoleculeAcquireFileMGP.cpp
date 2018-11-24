/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireFileMGP.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "MoleculeAcquireFileMGP.h"

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
vtkStandardNewMacro(MoleculeAcquireFileMGP);

//----------------------------------------------------------------------------
MoleculeAcquireFileMGP::MoleculeAcquireFileMGP() {}

//----------------------------------------------------------------------------
MoleculeAcquireFileMGP::~MoleculeAcquireFileMGP() {}

//----------------------------------------------------------------------------
vtkMolecule *MoleculeAcquireFileMGP::GetOutput()
{
  return vtkMolecule::SafeDownCast(this->GetOutputDataObject(0));
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileMGP::SetOutput(vtkMolecule *output)
{
  this->GetExecutive()->SetOutputData(0, output);
}

int MoleculeAcquireFileMGP::RequestInformation(
    vtkInformation *vtkNotUsed(request),
    vtkInformationVector **vtkNotUsed(inputVector),
    vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  if (!this->HasFileName())
    return 0;

  ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro("MoleculeAcquireFileMGP error opening file: " << this->FileName());
    return 0;
  }

  std::string str_line;
  std::string title;
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading title string: " << this->FileName());
    return 0;
  }
  title = str_line;

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading sizes string: " << this->FileName());
    return 0;
  }

  int nAtoms = 0;
  int nOrbs = 0;
  int nPrims = 0;
  std::string str_orb_type; // orbital type marker
  std::string skip;
  char cEq;
  std::istringstream ssinp(str_line);
  if (!(ssinp >> str_orb_type                // "SLATER" || "GTO" || "GAUSSIAN"
        >> nOrbs >> skip /* "MOL" */ >> skip // "ORBITALS"
        >> nPrims >> skip                    // "PRIMITIVES"
        >> nAtoms))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error: wrong SIZES string at " << this->FileName());
    return 0;
  }

  if ((nAtoms <= 0) || (nOrbs <= 0) || (nPrims <= 0))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error: wrong SIZES: nCenters=" << nAtoms
                  << " nOrbitals=" << nOrbs
                  << " nPrimitives=" << nPrims
                  << " at " << this->FileName());
    return 0;
  }

  assert(!this->GetNumberOfAtoms()); // assured that it is read first
  this->SetNumberOfAtoms(nAtoms);
  assert(!this->GetNumberOfPrimitives());
  this->SetNumberOfPrimitives(nPrims);
  assert(!this->GetNumberOfOrbitals());
  this->SetNumberOfOrbitals(nOrbs);

  for (int i = 0; i < nAtoms; i++)
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading atom string #" << i + 1 << " in " << this->FileName());
      return 0;
    }
  }

  int nTextSectionHeight = (nPrims + 19) / 20; // 20 ints per string; format constant
  for (int i = 0; i < nTextSectionHeight; ++i)
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading CENTRE ASSIGNMENTS string #" << (++i) << " in " << this->FileName());
      return 0;
    }
  }
  for (int i = 0; i < nTextSectionHeight; ++i)
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading TYPE ASSIGNMENTS string #" << (++i) << " in " << this->FileName());
      return 0;
    }
  }

  nTextSectionHeight = (nPrims + 4) / 5; // 5 reals per string; format constant

  for (int i = 0; i < nTextSectionHeight; ++i)
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading EXPONENTS string #" << (++i) << " in " << this->FileName());
      return 0;
    }
  }

  for (int j = 0; j < nOrbs; ++j)
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading ORBITAL #" << (++j) << " header in " << this->FileName());
      return 0;
    }
    for (int i = 0; i < nTextSectionHeight; ++i)
    {
      if (!std::getline(file_in, str_line))
      {
        vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading ORBITAL #" << (++j) << " in string #" << (++i) << " in " << this->FileName());
        return 0;
      }
    }
  }

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading END DATA string in " << this->FileName());
    return 0;
  }
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading ENERGY/VIRIAL string in " << this->FileName());
    return 0;
  }

  return 1;
}

int MoleculeAcquireFileMGP::RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *outVector)
{
  vtkInformation *outInfo = outVector->GetInformationObject(0);
  vtkMolecule *output = vtkMolecule::SafeDownCast(vtkDataObject::GetData(outVector));

  if (!output)
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP does not have a vtkMolecule as output.");
    return 1;
  }

  if (!this->HasFileName())
    return 0;

  ifstream file_in(this->GetFileName());

  if (!file_in.is_open())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error opening file: " << this->FileName());
    return 0;
  }

  std::string str_line;
  std::string title;

  // first non-empty string is the title
  do
  {
    if (!std::getline(file_in, str_line))
    {
      vtkErrorMacro("MoleculeAcquireFileMGP error: premature EOF while reading title from" << this->FileName());
      return 0;
    }
  } while (str_line.empty());

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro("MoleculeAcquireFileMGP error: premature EOF while reading sizes from" << this->FileName());
    return 0;
  }

  int nAtoms = 0;
  size_t nOrbs = 0, nPrims = 0;
  std::string str_orb_type; // orbital type marker
  std::string skip;
  char cEq;

  std::istringstream ssinp(str_line);
  if (!(ssinp >> str_orb_type                // "SLATER" || "GTO" || "GAUSSIAN"
        >> nOrbs >> skip /* "MOL" */ >> skip // "ORBITALS"
        >> nPrims >> skip                    // "PRIMITIVES"
        >> nAtoms))
  {
    vtkErrorMacro("MoleculeAcquireFileMGP error: wrong SIZES string at " << this->FileName());
    return 0;
  }

  if (nAtoms != this->GetNumberOfAtoms())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading atom number " << this->FileName()
                  << " Premature EOF while reading molecule.");
    // file_in.close();
    return 0;
  }

  // construct vtkMolecule
  int nResult = AppendAtoms(file_in, this->GetNumberOfAtoms(), output);
  if (nResult)
  {
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading atom #" << nResult
                    << " from " << this->FileName()
                    << " Premature EOF while reading molecule.");
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error parsing atom #" << -nResult
                    << " from " << this->FileName()
                    << " Premature EOF while reading molecule.");
    return 0;
  }

  // other stuff to read are to be written later

  return 1;
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileMGP::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  // os << indent << "Number of TimeSteps: " << this->NumberOfTimeSteps;
}