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
#include "TraitsAcquireAtoms.h"
#include "CriticalPoints.h"

#include <vtkObjectFactory.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;
using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileQTAIM);

//----------------------------------------------------------------------------
void MoleculeAcquireFileQTAIM::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "Critical points:"
    // << (this->HasFileName() ? this->GetFileName() : "(null)" ) 
    << std::endl;
}

//----------------------------------------------------------------------------
vtkIdType MoleculeAcquireFileQTAIM::ReadNumberCPs(istream &sin)
{
  vtkIdType nRes = 0;
  string str_one;
  getline(sin, str_one);
  do
  {
    if(str_one.empty())
    continue;
    if(!str_one.find("Total number of electron density critical points found ="))
    {
      istringstream inn(str_one.substr(57));
      inn >> nRes;
      break;
    }
  } while (getline(sin, str_one));

  this->ResetNumberOfCPs(nRes);
  return nRes;
}
