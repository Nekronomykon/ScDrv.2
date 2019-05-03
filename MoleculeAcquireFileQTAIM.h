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
#include "MoleculeAcquireFileQM.h"

#include <vtkSetGet.h>

class vtkMolecule;
class CriticalPoints;

namespace vtk
{

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MoleculeAcquireFileQTAIM
    : public MoleculeAcquireFileQM
{
  typedef MoleculeAcquireFileQM _Base;

public:
  static MoleculeAcquireFileQTAIM *New();
  vtkTypeMacro(MoleculeAcquireFileQTAIM, MoleculeAcquireFileQM);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  void Initialize(); // override;


  vtkIdType GetNumberOfCPs() const {return NumberOfCPs_;}
  vtkIdType ResetNumberOfCPs(vtkIdType nnew = 0)
  {
    if(nnew != this->GetNumberOfCPs())
    {
      std::swap(nnew,NumberOfCPs_);
      this->Modified();
    }
    return nnew;
  }

  template <typename Stream>
  int _ParseStreamData(Stream &src, vtkInformationVector *out)
  {
    int kBaseRes = 0; //_Base::ParseStreamData(src, out);
    if (kBaseRes)
    {
      //CriticalPoints *pCP = CriticalPoints::SafeDownCast(vtkDataObject::GetData(out, 1));
      // here we go down read all criticals:
      return kBaseRes;
    }
    return kBaseRes;
  }

protected:
  enum
  {
    AtomMaximumCP = 0,
    BondSaddleCP = 1,
    RingSaddleCP = 2,
    CageMinimumCP = 3,
    NonNuclearMaxCP = 4,
    NumberOfCPTypes = 5
  };

  explicit MoleculeAcquireFileQTAIM() = default;
  ~MoleculeAcquireFileQTAIM() override = default;

  vtkIdType ReadNumberCPs(std::istream& sin); 

private:
  MoleculeAcquireFileQTAIM(const MoleculeAcquireFileQTAIM &) = delete;
  void operator=(const MoleculeAcquireFileQTAIM &) = delete;

  vtkIdType NumberOfCPs_ = 0;
  vtkIdType CriticalPoints[NumberOfCPTypes];
};

}; // namespace vtk

#endif // !MoleculeAcquire_FileQTAIM_h
