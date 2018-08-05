#ifndef __MoleculeAcquire_File_h__
#define __MoleculeAcquire_File_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <ostream>

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireBase.h"
#include "ImplFileName.h"

#include <vtkStdString.h>

class MoleculeAcquireFile
    : public MoleculeAcquireBase
    , public ImplFileName<MoleculeAcquireFile,vtkStdString>
{
protected:
  typedef MoleculeAcquireBase::Molecule Molecule;

public:
  static MoleculeAcquireFile *New();
  vtkTypeMacro(MoleculeAcquireFile, MoleculeAcquireBase)
  void PrintSelf(std::ostream &os, vtkIndent indent) VTK_OVERRIDE;

protected:
  MoleculeAcquireFile();
  ~MoleculeAcquireFile() VTK_OVERRIDE;

private:
  MoleculeAcquireFile(const MoleculeAcquireFile &) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFile &) VTK_DELETE_FUNCTION;
};


#endif // !__MoleculeAcquire_File_h__
