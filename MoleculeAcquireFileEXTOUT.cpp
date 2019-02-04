/*=========================================================================

  Program:   Local Fork of the Visualization Toolkit (VTK) C++ Part
  Module:    MoleculeAcquireFileEXTOUT.cxx

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "MoleculeAcquireFileEXTOUT.h"
#include "TraitsAcquireAtoms.h"

#include <vtkObjectFactory.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;
using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileEXTOUT);

//----------------------------------------------------------------------------
int MoleculeAcquireFileEXTOUT::PreParseStream(BaseInput &infile)
{
  if (!Traits::ScrollDownTo(infile, " The nuclear coordinates:"))
    return 0;

  size_t nAtomStr = Traits::MeasureStringGroup(infile);

  if (!nAtomStr)
    return 0;

  assert(!this->GetNumberOfAtoms());
  this->SetNumberOfAtoms(nAtomStr);

  // Here could the specific QTAIM info be parsed...

  return 1;
}

//----------------------------------------------------------------------------
int MoleculeAcquireFileEXTOUT::ReadSimpleMolecule(BaseInput &infile, vtkMolecule *pMol)
{
  if (!Traits::ScrollDownTo(infile, " The nuclear coordinates:"))
    return 0;
  int nResult = Traits::AppendAtoms(infile, this->GetNumberOfAtoms(), pMol);

  if (nResult)
  {
    vtkErrorMacro("EXTOUT format is broken badly:" << endl);
    if (nResult > 0)
      vtkErrorMacro(<< "MoleculeAcquireFileEXTOUT error reading atom #" << nResult
        << " from " << this->FileName()
        << " Premature EOF while reading molecule."
      );
    if (nResult < 0)
      vtkErrorMacro(<< "MoleculeAcquireFileEXTOUT error parsing atom #" << -nResult
        << " from " << this->FileName()
        << " Premature EOF while reading molecule."
      );
    return 0;
  }

  return 1;
}

//----------------------------------------------------------------------------
//void MoleculeAcquireFileEXTOUT::PrintSelf(ostream& os, vtkIndent indent)
//{
//  _Base::PrintSelf(os, indent);
//}
//
//----------------------------------------------------------------------------
