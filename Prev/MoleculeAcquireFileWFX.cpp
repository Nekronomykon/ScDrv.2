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

#include <vtkMolecule.h>

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
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Title> section in " << this->path());
  }
  // this->ResetTitle(title);

  istringstream inpNAtoms(Traits::ReadTagContent(file_in, "Number of Nuclei"));
  inpNAtoms >> nAtoms;
  if (!nAtoms)
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Number of Nuclei> section in " << this->path());
    return 0;
  }
  this->ResetNumberOfAtoms(nAtoms);

  bufAtomNumbers_ = Traits::ReadTagContent(file_in, "Atomic Numbers");
  if (bufAtomNumbers_.empty())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Atomic Numbers> section in " << this->path());
    return 0;
  }

  bufAtomCoords_ = Traits::ReadTagContent(file_in, "Nuclear Cartesian Coordinates");
  if (bufAtomCoords_.empty())
  {
    vtkErrorMacro(<< "MoleculeAcquireFileWFX error reading <Nuclear Cartesian Coordinates> section in " << this->path());
    return 0;
  }

  return (nAtoms > 0) ? 1 : 0;
}

int MoleculeAcquireFileWFX::ReadMolecule(istream &file_in, vtkMolecule *pMol)
{
  string str_line;
  string title = Traits::ReadTagContent(file_in, "Title");
  istringstream inpANum(bufAtomNumbers_);
  istringstream inpAXYZ(bufAtomCoords_);
  istringstream inlALbl(bufAtomLabels_);

  int nAtomsReq = this->GetNumberOfAtoms();
  size_t nOrbs = this->GetNumberOfOrbitals();
  size_t nPrims = this->GetNumberOfPrimitives();

  size_t idAtomType = 0;
  size_t idx = 0;
  inpANum >> idAtomType;
  if (!Elements::IsValidAtomNumber(idAtomType))
    return 0;
  do
  {
    double x,y,z;
    inpAXYZ >> x >> y >> z;
    vtkAtom atom_new = pMol->AppendAtom(idAtomType, x, y, z);

    ++idx;
    --nAtomsReq;
    idAtomType = 0;
    inpANum >> idAtomType;
  } while (Elements::IsValidAtomNumber(idAtomType));

  return (!nAtomsReq) ? 1 : 0;
}

//----------------------------------------------------------------------------
// void MoleculeAcquireFileWFX::PrintSelf(ostream &os, vtkIndent indent)
// {
//   this->Superclass::PrintSelf(os, indent);
//   // os << indent << "Number of TimeSteps: " << this->NumberOfTimeSteps;
// }
