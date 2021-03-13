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
  CriticalPoints *GetCriticalOutputAt(int /* port */);
  void SetCriticalOutput(CriticalPoints *, bool /*bUpdateMol*/ = false);

  void Initialize(); // override;
  int FillOutputPortInformation(int, vtkInformation *) override;

  vtkIdType GetCriticalPointNumber() const { return NumberCritPoint_; }
  vtkIdType ResetCriticalPointNumber(vtkIdType nnew = 0)
  {
    if (nnew != this->GetCriticalPointNumber())
    {
      std::swap(nnew, NumberCritPoint_);
      this->Modified();
    }
    return nnew;
  }

  int ParseStreamData(std::istream & /*src*/,
                      vtkInformationVector * /*out*/) override;

  vtkIdType ReadCriticalInfo(std::istream & /* input */, vtkInformationVector* /* info */);
  virtual int ReadCriticalData(std::istream &, CriticalPoints *);

protected:

  explicit MoleculeAcquireFileQTAIM();
  ~MoleculeAcquireFileQTAIM() override = default;

private:
  MoleculeAcquireFileQTAIM(const MoleculeAcquireFileQTAIM &) = delete;
  void operator=(const MoleculeAcquireFileQTAIM &) = delete;

  vtkIdType NumberCritPoint_ = 0;
};

}; // namespace vtk

#endif // !MoleculeAcquire_FileQTAIM_h
