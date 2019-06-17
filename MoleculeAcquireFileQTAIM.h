#ifndef MoleculeAcquire_FileQTAIM_h
#define MoleculeAcquire_FileQTAIM_h

/*=========================================================================

  Program:   Visualization Toolkit Local Copy
  Module:    MoleculeAcquireFileQTAIM.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileQTAIM
 * @brief   Reads a data file associated with the QTAIM calculation results
 * outputs a vtkMolecule object and some other data bound to it
 *
 * NOT YET FINISHED!
 *
 * @par Thanks:
 * ScrewDriver te Blackheadborough who developed and contributed this class
 *
 * NB: It is preconverted from the MoleculeAcquireFileCUBE class
 * and yet not in its final executive form.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireFileField.h"

#include "CriticalPoints.h"

#include <vtkSetGet.h>

#include <istream>

class vtkMolecule;
class CriticalPoints;

namespace vtk
{

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MoleculeAcquireFileQTAIM
    : public MoleculeAcquireFileField
{
  typedef MoleculeAcquireFileField _Base;

public:
  static MoleculeAcquireFileQTAIM *New();
  vtkTypeMacro(MoleculeAcquireFileQTAIM, MoleculeAcquireFileField);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  enum
  {
    PortCritical = 2
  };

  CriticalPoints *GetCriticalOutput();
  CriticalPoints *GetCriticalOutput(int);
  void SetCriticalOutput(CriticalPoints *, bool /*bUpdateMol*/ = false);

  void Initialize(); // override;

  vtkIdType GetNumberOfCPs() const { return NumberOfCPs_; }
  vtkIdType ResetNumberOfCPs(vtkIdType nnew = 0)
  {
    if (nnew != this->GetNumberOfCPs())
    {
      std::swap(nnew, NumberOfCPs_);
      this->Modified();
    }
    return nnew;
  }

  int ParseStreamData(std::istream & /*src*/,
                      vtkInformationVector * /*out*/) override;

protected:
  virtual int ReadCritical(std::istream &, CriticalPoints *);

  explicit MoleculeAcquireFileQTAIM();
  ~MoleculeAcquireFileQTAIM() override = default;

  vtkIdType ReadNumberCPs(std::istream &sin);

private:
  MoleculeAcquireFileQTAIM(const MoleculeAcquireFileQTAIM &) = delete;
  void operator=(const MoleculeAcquireFileQTAIM &) = delete;

  vtkIdType NumberOfCPs_ = 0;
};

}; // namespace vtk

#endif // !MoleculeAcquire_FileQTAIM_h
