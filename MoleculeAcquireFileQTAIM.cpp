/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileQTAIM.cpp

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notice for more information.

  =========================================================================*/

#include "MoleculeAcquireFileQTAIM.h"

#include <vtkObjectFactory.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileQTAIM);

//----------------------------------------------------------------------------
MoleculeAcquireFileQTAIM::MoleculeAcquireFileQTAIM()
  : NumberOfOrbitals_(0)      // empty space...
  , NumberOfPrimitives_(0)    // empty basis...
{}

//----------------------------------------------------------------------------
MoleculeAcquireFileQTAIM::~MoleculeAcquireFileQTAIM()
{}

//----------------------------------------------------------------------------
void MoleculeAcquireFileQTAIM::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "Critical points:"
    // << (this->HasFileName() ? this->GetFileName() : "(null)" ) 
    << std::endl;
}
