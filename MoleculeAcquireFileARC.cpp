/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module : MoleculeAcquireFileARC.cxx

  Copyright(c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.See the above copyright notice for more information.

  ======================================================================== = */

#include "MoleculeAcquireFileARC.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>

#include <vtkMolecule.h>
#include <vtkPeriodicTable.h>

#include <vtkStreamingDemandDrivenPipeline.h>

#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileARC);

MoleculeAcquireFileARC::MoleculeAcquireFileARC()
  : MoleculeAcquireFile()
{
}


MoleculeAcquireFileARC::~MoleculeAcquireFileARC(){}
