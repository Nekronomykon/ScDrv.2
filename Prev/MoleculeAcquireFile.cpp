/*=========================================================================

Program:   Visualization Toolkit Local Copy
Module:    MoleculeAcquireFile.cpp

Copyright (c) ScrewDriver te Blackheadborough
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "MoleculeAcquireFile.h"

#include <vtkObjectFactory.h>

using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFile);

//----------------------------------------------------------------------------
MoleculeAcquireFile::MoleculeAcquireFile(int nOutPorts)
: MoleculeAcquireBase(nOutPorts)
{
  this->SetNumberOfInputPorts(0); // only internal generation
}

//----------------------------------------------------------------------------
void MoleculeAcquireFile::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  bool bHas = this->hasPath();

  os << indent << "FileName"
    << (bHas ? this->getPath() : "(null)");
  os << std::endl;
}
