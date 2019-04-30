/*=========================================================================

  Program:   Local Fork of the Visualization Toolkit (VTK) C++ Part
  Module:    MoleculeAcquireFileWFX.cxx

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "MoleculeAcquireFileWFX.h"
#include "TraitsAcquireAtoms.h"

#include <vtkObjectFactory.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;
using namespace vtk;


//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileWFX);

int MoleculeAcquireFileWFX::ParseStreamInfo(BaseInput &file_in, vtkInformationVector *)
{
  vtkIdType nAtoms(0);
  string title(Traits::ReadTagContent(file_in, "Title"));
  if (title.empty())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Title> section in " << this->FileName());
  }
  // this->ResetTitle(title);

  istringstream inpNAtoms(Traits::ReadTagContent(file_in, "Number of Nuclei"));
  inpNAtoms >> nAtoms;
  if (!nAtoms)
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Number of Nuclei> section in " << this->FileName());
    return 0;
  }
  this->ResetNumberOfAtoms(nAtoms);

  if (Traits::ReadTagContent(file_in, "Atomic Numbers").empty())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Atomic Numbers> section in " << this->FileName());
    return 0;
  }

  if (Traits::ReadTagContent(file_in, "Nuclear Cartesian Coordinates").empty())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Nuclear Cartesian Coordinates> section in " << this->FileName());
    return 0;
  }

  return (nAtoms > 0)? 1 : 0;
}

int MoleculeAcquireFileWFX::ReadSimpleMolecule(BaseInput &file_in, Molecule *pMol)
{
  string str_line;
  string title = Traits::ReadTagContent(file_in, "Title");
  istringstream inpNumers(Traits::ReadTagContent(file_in, "Atomic Numbers"));
  istringstream inpXYZ(Traits::ReadTagContent(file_in, "Nuclear Cartesian Coordinates"));
  istringstream inlLabels(Traits::ReadTagContent(file_in, "Nuclear Names"));

  // first non-empty string is the title
  do
  {
    if (!getline(file_in, str_line))
    {
      vtkErrorMacro("MoleculeAcquireFileWFX error: premature EOF while reading title from" << this->FileName());
      return 0;
    }
  } while (str_line.empty());

  if (!getline(file_in, str_line))
  {
    vtkErrorMacro("MoleculeAcquireFileWFX error: premature EOF while reading sizes from" << this->FileName());
    return 0;
  }

  int nAtoms = 0;
  size_t nOrbs = 0, nPrims = 0;
  string str_orb_type; // orbital type marker
  string skip;
  char cEq;

  istringstream ssinp(str_line);
  if (!(ssinp >> str_orb_type                // "SLATER" || "GTO" || "GAUSSIAN"
        >> nOrbs >> skip /* "MOL" */ >> skip // "ORBITALS"
        >> nPrims >> skip                    // "PRIMITIVES"
        >> nAtoms))
  {
    vtkErrorMacro("MoleculeAcquireFileWFX error: wrong SIZES string at " << this->FileName());
    return 0;
  }

  if (nAtoms != this->GetNumberOfAtoms())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading atom number " << this->FileName()
                  << " Premature EOF while reading molecule.");
    // file_in.close();
    return 0;
  }

  // construct vtkMolecule
  int nResult = 0;
  // nResult = Traits::AppendAtoms(file_in, this->GetNumberOfAtoms(), pMol);
  if (nResult)
  {
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading atom #" << nResult
                    << " from " << this->FileName()
                    << " Premature EOF while reading molecule.");
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileWFX error parsing atom #" << -nResult
                    << " from " << this->FileName()
                    << " Premature EOF while reading molecule.");
    return 0;
  }

  return 1;
}

//----------------------------------------------------------------------------
// void MoleculeAcquireFileWFX::PrintSelf(ostream &os, vtkIndent indent)
// {
//   this->Superclass::PrintSelf(os, indent);
//   // os << indent << "Number of TimeSteps: " << this->NumberOfTimeSteps;
// }
