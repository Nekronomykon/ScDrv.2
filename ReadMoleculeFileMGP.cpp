#include "ReadMoleculeFileMGP.h"

using namespace vtk;


#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkMolecule.h>
#include <vtkObjectFactory.h>
#include <vtkPeriodicTable.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtksys/FStream.hxx>

#include <cmath>
#include <cstring>
#include <sstream>

//------------------------------------------------------------------------------
vtkStandardNewMacro(ReadMoleculeFileMGP);

//------------------------------------------------------------------------------
vtkMolecule* ReadMoleculeFileMGP::GetOutput()
{
  return vtkMolecule::SafeDownCast(this->GetOutputDataObject(0));
}

//------------------------------------------------------------------------------
void ReadMoleculeFileMGP::SetOutput(vtkMolecule* output)
{
  this->GetExecutive()->SetOutputData(0, output);
}

ReadMoleculeFileMGP::ReadMoleculeFileMGP()
: ReadMoleculeFileBase()
{
  this->SetNumberOfInputPorts(0);
}

//------------------------------------------------------------------------------
void ReadMoleculeFileMGP::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "FileName: " << this->FileName << endl;
}
