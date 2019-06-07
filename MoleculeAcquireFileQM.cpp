/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileQM.cpp

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notice for more information.

  =========================================================================*/

#include "MoleculeAcquireFileQM.h"
#include "TraitsAcquireAtoms.h"
#include "CriticalPoints.h"

#include <vtkObjectFactory.h>

using namespace std;
using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileQM);

//----------------------------------------------------------------------------
MoleculeAcquireFileQM::MoleculeAcquireFileQM(int nOutPorts)
    : MoleculeAcquireFile(nOutPorts)
    , NumberOfOrbitals_(0)
    , NumberOfPrimitives_(0)
{
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileQM::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Orbitals = " << this->GetNumberOfOrbitals() << std::endl
     << indent << "Primitives = " << this->GetNumberOfPrimitives() << std::endl;
}
