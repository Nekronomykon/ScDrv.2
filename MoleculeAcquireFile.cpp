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
MoleculeAcquireFile::MoleculeAcquireFile()
  : posRead_(0L)
{
  this->SetNumberOfInputPorts(0);
}

//----------------------------------------------------------------------------
void MoleculeAcquireFile::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  bool bHas = this->HasFileName();

  os << indent << "FileName"
    << (bHas ? this->GetFileName() : "(null)");
  if (bHas) os << "@Pos: " << (unsigned long)posRead_;
  os << std::endl;
}
