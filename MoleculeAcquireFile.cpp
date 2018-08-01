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

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFile);

//----------------------------------------------------------------------------
MoleculeAcquireFile::MoleculeAcquireFile()
{
  this->SetNumberOfInputPorts(0);
}

//----------------------------------------------------------------------------
MoleculeAcquireFile::~MoleculeAcquireFile() {}

//----------------------------------------------------------------------------
void MoleculeAcquireFile::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "FileName"
    << (this->HasFileName() ? this->GetFileName() : "(null)") << std::endl;
}
