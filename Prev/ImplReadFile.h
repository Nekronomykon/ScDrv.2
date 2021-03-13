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

#include "MoleculeAcquireFile.h"
#include "ImplFileName.h"
#include "TraitsAcquireAtoms.h"

template <class T,
          template <typename U> class TTraits, // = TraitsEmpty
          class TBase                          // = MoleculeAcquireBase
          >
class ImplReadFile
    : public TBase
// , public TTraits<T>
{
  typedef TBase _Base;
  typedef TTraits<T> Traits;

public:
  typedef typename Traits::BaseInput BaseInput;
  typedef typename TBase::Molecule Molecule;
  void PrintSelf(std::ostream &os, vtkIndent indent) override
  {
    T *pT = static_cast<T *>(this);
    pT->PrintBefore(os, indent);
    _Base::PrintSelf(os, indent);
    pT->PrintBeyond(os, indent);
  }

  void PrintBefore(std::ostream &, vtkIndent) {}
  void PrintBeyond(std::ostream &, vtkIndent) {}

  int RequestInformation(vtkInformation *, vtkInformationVector **inInfo, vtkInformationVector *outputVector) override
  {
    vtkInformation *outInfo = outputVector->GetInformationObject(0);
    T *pT = static_cast<T *>(this);

    if (!pT->hasPath())
      return 0;

    std::ifstream file_in(pT->getPath());

    if (!file_in.is_open())
    {
      vtkErrorMacro(<< "ImplReadFile<> error opening file: " << pT->path());
      return 0;
    }

    return pT->ParseStreamInfo(file_in, outputVector);
  }

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *outputVector) override
  {
    T *pT = static_cast<T *>(this);

    if (!pT->hasPath())
      return 0;

    std::ifstream file_in(pT->getPath());

    if (!file_in.is_open())
    {
      vtkErrorMacro(<< "Error opening file: " << pT->path());
      return 0;
    }

    return pT->ParseStreamData(file_in, outputVector);
  }

  int ParseStreamInfo(BaseInput &, vtkInformationVector *out)
  {
    if (!out)
      return 0;
    vtkInformation *outInfo = out->GetInformationObject(0);
    return outInfo ? 1 : 0;
  }

  int ReadSimpleMolecule(BaseInput &, Molecule *)
  {
    assert(0);
    return 1;
  }

protected:
  explicit ImplReadFile() = default;
  ~ImplReadFile() override = default;

private:
  ImplReadFile(const ImplReadFile &) = delete;
  void operator=(const ImplReadFile &) = delete;
};

#endif // !Impl_ReadFile_h
