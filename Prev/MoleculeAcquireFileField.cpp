/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileField
.cpp

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notice for more information.

  =========================================================================*/

#include "MoleculeAcquireFileField.h"
#include "TraitsAcquireAtoms.h"
#include "CriticalPoints.h"

#include <vtkObjectFactory.h>
#include <vtkExecutive.h>
#include <vtkImageData.h>

using namespace std;
using namespace vtk;

//----------------------------------------------------------------------------
vtkStandardNewMacro(MoleculeAcquireFileField);

//----------------------------------------------------------------------------
MoleculeAcquireFileField::MoleculeAcquireFileField(int nOutPorts)
    : MoleculeAcquireFile(nOutPorts), NumberOfOrbitals_(0), NumberOfPrimitives_(0)
{
  vtkImageData *grid;
  grid = vtkImageData::New();
  grid->ReleaseData();
  this->GetExecutive()->SetOutputData(PortGrid, grid);
  grid->Delete();
}

//----------------------------------------------------------------------------
void MoleculeAcquireFileField::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Orbitals = " << this->GetNumberOfOrbitals() << std::endl
     << indent << "Primitives = " << this->GetNumberOfPrimitives() << std::endl;
}

/**
   * Get/Set the output (vtkImageData) that the reader will fill
   */
vtkImageData *MoleculeAcquireFileField::GetGridOutput()
{
  if (this->GetNumberOfOutputPorts() <= PortGrid)
    return nullptr;

  return vtkImageData::SafeDownCast(this->GetOutputDataObject(PortGrid));
}

int MoleculeAcquireFileField::FillOutputPortInformation(int port, vtkInformation *info)
{
  if (port == PortMolecule)
    return this->Superclass::FillOutputPortInformation(port, info);

  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkImageData");
  return 1;
}

