#ifndef MoleculeAcquire_File_h
#define MoleculeAcquire_File_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <ostream>
#include <istream>
#include <fstream>

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireBase.h"
#include "ImplFileName.h"

#include "TraitsAcquireAtoms.h"

#include <vtkStdString.h>

class MoleculeAcquireFile
    : public MoleculeAcquireBase
    , public ImplFileName<MoleculeAcquireFile,vtkStdString>
{
protected:
  typedef MoleculeAcquireBase::Molecule Molecule;
  typedef std::ifstream FileInput;
  typedef FileInput::pos_type FileInputPos;

public:
  static MoleculeAcquireFile *New();
  vtkTypeMacro(MoleculeAcquireFile, MoleculeAcquireBase)
  void PrintSelf(std::ostream &os, vtkIndent indent) VTK_OVERRIDE;

  //
  // void ResetPos(FileInputPos pos) { posRead_ = pos; }
  // FileInputPos GetPos(FileInputPos pos) const { return posRead_; }
  // std::ifstream& Scroll(std::ifstream& is) const { return is.seekg(posRead_,SEEK_SET); }

protected:
  explicit MoleculeAcquireFile();
  ~MoleculeAcquireFile() VTK_OVERRIDE;

private:
  MoleculeAcquireFile(const MoleculeAcquireFile &) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFile &) VTK_DELETE_FUNCTION;

  // members:
private:
  FileInputPos posRead_;
};


#endif // !MoleculeAcquire_File_h
