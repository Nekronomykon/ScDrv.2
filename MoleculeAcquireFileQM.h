#ifndef MoleculeAcquire_FileQM_h
#define MoleculeAcquire_FileQM_h

/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileQM.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileQM
 * @brief   Reads a data file associated with the quantum chemical calculation 
 * results; outputs a vtkMolecule object and some other data bound to it
 *
 * NOT YET FINISHED!
 *
 * @par Thanks:
 * ScrewDriver de Blackheadborough who developed and contributed this class
 *
 * NB: It is preconverted from the MoleculeAcquireFileCUBE class
 * and yet not in its final executive form.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireFile.h"

#include <vtkSetGet.h>

#include <istream>

class vtkMolecule;

namespace vtk
{

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MoleculeAcquireFileQM
    : public MoleculeAcquireFile
{
  typedef MoleculeAcquireFile _Base;

public:
  static MoleculeAcquireFileQM *New();
  vtkTypeMacro(MoleculeAcquireFileQM, MoleculeAcquireFile);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  vtkIdType GetNumberOfOrbitals() const { return NumberOfOrbitals_; }
  virtual vtkIdType ResetNumberOfOrbitals(vtkIdType nnew = 0)
  {
    if (nnew != this->GetNumberOfOrbitals())
    {
      std::swap(NumberOfOrbitals_, nnew);
      this->Modified();
    }
    return nnew;
  }

  vtkIdType GetNumberOfPrimitives() const { return NumberOfPrimitives_; }
  vtkIdType ResetNumberOfPrimitives(vtkIdType nnew = 0)
  {
    if (nnew != GetNumberOfPrimitives())
    {
      std::swap(NumberOfPrimitives_, nnew);
      this->Modified();
    }
    return nnew;
  }

  int ParseStreamData(std::istream &src, vtkInformationVector *out) override
  {
    if (!_Base::ParseStreamData(src, out))
      return 0;

    // if electronics is not available, it is almost Ok

    return this->ParseElectronicData(src, out);
  }

  virtual int ParseElectronicData(std::istream &src, vtkInformationVector *out)
  {
    return 1;
  }

protected:
  MoleculeAcquireFileQM();
  ~MoleculeAcquireFileQM() override = default;

private:
  MoleculeAcquireFileQM(const MoleculeAcquireFileQM &) = delete;
  void operator=(const MoleculeAcquireFileQM &) = delete;

private:
  vtkIdType NumberOfOrbitals_ = 0;
  vtkIdType NumberOfPrimitives_ = 0;
};

}; // namespace vtk

#endif // !MoleculeAcquire_FileQM_h
