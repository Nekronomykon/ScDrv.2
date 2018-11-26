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
  int MoleculeAcquireFileOUT:: PreParseStream(BaseInput & file_in)
{
  int natoms = 0;
  string str_line;

  if (!std::getline(file_in, str_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileOUT error: premature EOF in " << this->FileName());
    return 0;
  }
  do
  {
    if (str_line.size() < 50
      || str_line.compare(29, 21, "CARTESIAN COORDINATES"))
      continue;

    // init scan results:
    natoms = Traits::MeasureStringGroup(file_in);
    assert(natoms > 0);
    this->SetNumberOfAtoms(natoms);
    break;

  } while (getline(file_in, str_line));

  return natoms;
}

//----------------------------------------------------------------------------
int MoleculeAcquireFileOUT::ReadSimpleMolecule(BaseInput & file_in, Molecule *output)
{
  int timestep = 0;
  int nbAtoms = 0;
  string str_line;

  int natoms = 0;
  int nResult = -1;

  if (!getline(file_in, str_line))
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
      if (!getline(file_in, str_line))
      {
        vtkErrorMacro(<< "MoleculeAcquireFileOUT error: premature EOF in " << this->FileName());
        return 0;
      }

      // init scan results:
      nResult = Traits::AppendAtoms(file_in, this->GetNumberOfAtoms(), output);
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
  } while ((bool)getline(file_in, str_line));

  return (nResult) ? 0 : 1;
}
