#ifndef Impl_ReadFile_h
#define Impl_ReadFile_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkDataObject.h>
#include <vtkStdString.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkMolecule.h>

#include "MoleculeAcquireBase.h"
#include "ImplFileName.h"
#include "TraitsAcquireAtoms.h"

template<class T
  , template <class U> class TTraits = TraitsEmpty
  , class TBase = MoleculeAcquireFile
  , class TName = vtkStdString
>
class ImplReadFile
  : public TBase
  , public TTraits<T>
  // , public ImplFileName<T, TName>
{
  typedef TBase _Base;
public:
  typedef TraitsBase::BaseInput BaseInput;
  void PrintSelf(std::ostream &os, vtkIndent indent) override
  {
    T* pT = static_cast<T*>(this);
    pT->PrintBefore(os, indent);
    _Base::PrintSelf(os, indent);
    pT->PrintBeyond(os, indent);
  }

  void PrintBefore(std::ostream&, vtkIndent) {}
  void PrintBeyond(std::ostream&, vtkIndent) {}

  int RequestInformation(vtkInformation *
    , vtkInformationVector **
    , vtkInformationVector * outputVector) override
  {
    vtkInformation* outInfo = outputVector->GetInformationObject(0);
    T* pT = static_cast<T*>(this);

    if (!pT->HasFileName())
      return 0;

    std::ifstream file_in(pT->GetFileName());

    if (!file_in.is_open())
    {
      vtkErrorMacro(<< "MoleculeAcquireFileXYZ error opening file: " << pT->FileName());
      return 0;
    }

    return pT->PreParseStream(file_in);
  }

  int RequestData(vtkInformation *
    , vtkInformationVector **
    , vtkInformationVector * outputVector) override
  {
    vtkInformation* outInfo = outputVector->GetInformationObject(0);
    vtkMolecule *output = vtkMolecule::SafeDownCast(vtkDataObject::GetData(outputVector));

    if (!output)
    {
      vtkErrorMacro(<< "We do not have a vtkMolecule as output.");
      return 1;
    }

    T* pT = static_cast<T*>(this);

    if (!pT->HasFileName())
      return 0;

    std::ifstream file_in(pT->GetFileName());

    if (!file_in.is_open())
    {
      vtkErrorMacro(<< "Error opening file: " << pT->FileName());
      return 0;
    }

    return pT->ReadSimpleMolecule(file_in,output);
  }

  int PreParseStream(BaseInput&) { assert(0); return 1; }
  int ReadSimpleMolecule(BaseInput&,vtkMolecule*) { assert(0); return 1; }

protected:
  ImplReadFile() = default;
  ~ImplReadFile() override = default;

private:
  ImplReadFile(const ImplReadFile&) = delete;
  void operator =(const ImplReadFile&) = delete;
};

#endif // !Impl_ReadFile_h

