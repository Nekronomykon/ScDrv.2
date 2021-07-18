#include "ReadMoleculeFileMGP.h"

using namespace vtk;

//------------------------------------------------------------------------------
vtkStandardNewMacro(ReadMoleculeFileMGP);

ReadMoleculeFileMGP::ReadMoleculeFileMGP()
{
}

//------------------------------------------------------------------------------
void ReadMoleculeFileMGP::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "FileName: " << this->FileName << endl;
}
