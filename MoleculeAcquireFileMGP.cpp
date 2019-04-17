/*=========================================================================
  Program:   Local Fork of the Visualization Toolkit (VTK) C++ Part
  Module:    MoleculeAcquireFileMGP.cxx

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "MoleculeAcquireFileMGP.h"
#include "TraitsAcquireAtoms.h"

#include <vtkObjectFactory.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;
using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileMGP);

//----------------------------------------------------------------------------
int MoleculeAcquireFileMGP::ParseStreamInfo(BaseInput &infile,vtkInformationVector*)
{
  if (!Traits::ScrollDownTo(infile, "Nuclear Charges and Cartesian Coordinates:"))
    return 0;
  string one_line;
  if(!getline(infile,one_line) || !getline(infile, one_line) || !getline(infile, one_line))
  {
    vtkErrorMacro(<< "MoleculeAcquireFileMGP unexpectedly finished in " << this->FileName());
    return 0;
  }

  size_t nAtomStr = Traits::MeasureStringGroup(infile);
  if (!nAtomStr)
    return 0;
  assert(!this->GetNumberOfAtoms());
  this->SetNumberOfAtoms( nAtomStr );

  // Here could the specific QTAIM info be parsed...
  this->ReadNumberCPs(infile);

  return 1;
}

//----------------------------------------------------------------------------.S
int MoleculeAcquireFileMGP::ReadSimpleMolecule(BaseInput &infile, vtkMolecule *pMol)
{
  if (!Traits::ScrollDownTo(infile, "Nuclear Charges and Cartesian Coordinates:"))
    return 0;
  string one_line;
  if (!getline(infile, one_line) || !getline(infile, one_line) || !getline(infile, one_line))
  {
    vtkErrorMacro(<< "MGP file is unexpectedly finished: " << this->FileName());
    return 0;
  }
  int nResult = Traits::AppendAtoms(infile, this->GetNumberOfAtoms(), pMol);
  if (nResult)
  {
    vtkErrorMacro("MGP format is broken badly:" << endl);
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error reading atom #" << nResult
        << " from " << this->FileName()
        << " Premature EOF while reading molecule."
      );
    if (nResult < 0)
      vtkErrorMacro(<< "MoleculeAcquireFileMGP error parsing atom #" << -nResult
        << " from " << this->FileName()
        << " Premature EOF while reading molecule."
      );
    return 0;
  }
  return 1;
}

//----------------------------------------------------------------------------
//void MoleculeAcquireFileMGP::PrintSelf(ostream& os, vtkIndent indent)
//{
//  _Base::PrintSelf(os, indent);
//}
//
//----------------------------------------------------------------------------
