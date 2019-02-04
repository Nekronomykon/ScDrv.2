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

// #include <vtkStreamingDemandDrivenPipeline.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;
using namespace vtk;

#include "TraitsAcquireAtoms.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileXYZ);

//----------------------------------------------------------------------------
int MoleculeAcquireFileXYZ::PreParseStream(BaseInput& file_in)
{
  int natoms = 0;
  // istream::pos_type current_pos = file_in.tellg();
  string str_line;
  if (!getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading number of atoms:" << this->FileName());
    return 0;
  }
  istringstream ssinp(str_line);
  ssinp >> natoms;

  assert(!this->GetNumberOfAtoms()); // assured that it is read first
  this->SetNumberOfAtoms(natoms);

  string title;
  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading title string: " << this->FileName());
    return 0;
  }

  int nStrings = Traits::MeasureStringGroup(file_in);

  return (nStrings >= natoms) ? 1 : 0;
}

int MoleculeAcquireFileXYZ::ReadSimpleMolecule(BaseInput& file_in, Molecule*output)
{
  int timestep = 0;
  int nbAtoms = 0;
  string str_line;

  if (!getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading number of atoms:" << this->FileName());
    return 0;
  }
  istringstream ssinp(str_line);
  ssinp >> nbAtoms;
  // file_in.get(); // end of line char

  if (nbAtoms != this->GetNumberOfAtoms())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileXYZ error reading atom number " << this->FileName()
      << " Premature EOF while reading molecule.");
    return 0;
  }
  string title;
  getline(file_in, title);  // second line is a title

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
//void MoleculeAcquireFileXYZ::PrintSelf(ostream& os, vtkIndent indent)
//{
//  _Base::PrintSelf(os, indent);
//}
//
//----------------------------------------------------------------------------
