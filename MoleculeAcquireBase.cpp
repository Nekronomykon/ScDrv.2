/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireBase.cpp

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "MoleculeAcquireBase.h"

#include <vtkCommand.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>
#include <vtkMolecule.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkTrivialProducer.h>

vtkStandardNewMacro(MoleculeAcquireBase);

//----------------------------------------------------------------------------
MoleculeAcquireBase::MoleculeAcquireBase()
  : NumberOfAtoms_(0L)
{
  // by default assume filters have one output
  // subclasses that deviate should modify this setting
  //this->SetNumberOfInputPorts(1);
  this->SetNumberOfOutputPorts(1);
}

//----------------------------------------------------------------------------
MoleculeAcquireBase::~MoleculeAcquireBase() {}

//----------------------------------------------------------------------------
void MoleculeAcquireBase::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Number of Atoms: " << this->GetNumberOfAtoms() << endl;
}

//----------------------------------------------------------------------------
MoleculeAcquireBase::Molecule *MoleculeAcquireBase::GetOutput()
{
  return this->GetOutput(0);
}

//----------------------------------------------------------------------------
MoleculeAcquireBase::Molecule *MoleculeAcquireBase::GetOutput(int port)
{
  return Molecule::SafeDownCast(this->GetOutputDataObject(port));
}

//----------------------------------------------------------------------------
void MoleculeAcquireBase::SetOutput(MoleculeAcquireBase::Molecule *d)
{
  this->GetExecutive()->SetOutputData(0, d);
}

//----------------------------------------------------------------------------
vtkDataObject *MoleculeAcquireBase::GetInput()
{
  return this->GetInput(0);
}

//----------------------------------------------------------------------------
vtkDataObject *MoleculeAcquireBase::GetInput(int port)
{
  return this->GetExecutive()->GetInputData(port, 0);
}

//----------------------------------------------------------------------------
MoleculeAcquireBase::Molecule *MoleculeAcquireBase::GetMoleculeInput(int port)
{
  return Molecule::SafeDownCast(this->GetInput(port));
}

//----------------------------------------------------------------------------
int MoleculeAcquireBase::ProcessRequest(vtkInformation *request,
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  // generate the data
  if (request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
  {
    return this->RequestData(request, inputVector, outputVector);
  }

  if (request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
  {
    return this->RequestUpdateExtent(request, inputVector, outputVector);
  }

  // execute information
  if (request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
  {
    return this->RequestInformation(request, inputVector, outputVector);
  }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int MoleculeAcquireBase::FillOutputPortInformation(
  int vtkNotUsed(port), vtkInformation *info)
{
  // now add our info
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkMolecule");
  return 1;
}

//----------------------------------------------------------------------------
int MoleculeAcquireBase::FillInputPortInformation(
  int vtkNotUsed(port), vtkInformation *info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkMolecule");
  return 1;
}

//----------------------------------------------------------------------------
int MoleculeAcquireBase::RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *vtkNotUsed(outputVector))
{
  // do nothing let subclasses handle it
  return 1;
}

//----------------------------------------------------------------------------
int MoleculeAcquireBase::RequestUpdateExtent(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *vtkNotUsed(outputVector))
{
  int numInputPorts = this->GetNumberOfInputPorts();
  for (int i = 0; i < numInputPorts; i++)
  {
    int numInputConnections = this->GetNumberOfInputConnections(i);
    for (int j = 0; j < numInputConnections; j++)
    {
      vtkInformation *inputInfo = inputVector[i]->GetInformationObject(j);
      inputInfo->Set(vtkStreamingDemandDrivenPipeline::EXACT_EXTENT(), 1);
    }
  }
  return 1;
}

//----------------------------------------------------------------------------
// This is the superclasses style of Execute method.  Convert it into
// an imaging style Execute method.
int MoleculeAcquireBase::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *vtkNotUsed(outputVector))
{
  return 1;
}

//----------------------------------------------------------------------------
void MoleculeAcquireBase::SetInputData(vtkDataObject *input)
{
  this->SetInputData(0, input);
}

//----------------------------------------------------------------------------
void MoleculeAcquireBase::SetInputData(int index, vtkDataObject *input)
{
  this->SetInputDataInternal(index, input);
}

//----------------------------------------------------------------------------
void MoleculeAcquireBase::AddInputData(vtkDataObject *input)
{
  this->AddInputData(0, input);
}

//----------------------------------------------------------------------------
void MoleculeAcquireBase::AddInputData(int index, vtkDataObject *input)
{

  this->AddInputDataInternal(index, input);
}
