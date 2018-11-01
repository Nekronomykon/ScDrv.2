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
#include "MoleculeAcquireFile.h"

#include <vtkSetGet.h>

#include <complex>

class vtkMolecule;

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MoleculeAcquireFileQTAIM
    : public MoleculeAcquireFile
{
public:
  static MoleculeAcquireFileQTAIM *New();
  vtkTypeMacro(MoleculeAcquireFileQTAIM,MoleculeAcquireFile);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  vtkIdType GetNumberOfOrbitals() const { return NumberOfOrbitals_; }
  virtual vtkIdType SetNumberOfOrbitals(vtkIdType nnew)
  {
    if(nnew != this->GetNumberOfOrbitals())
    {
      std::swap(NumberOfOrbitals_, nnew);
      this->Modified();
    }
    return nnew;
  }

  vtkIdType GetNumberOfPrimitives() const { return NumberOfPrimitives_; }
  vtkIdType SetNumberOfPrimitives(vtkIdType nnew)
  {
    if(nnew != GetNumberOfPrimitives())
    {
      std::swap(NumberOfPrimitives_, nnew);
      this->Modified();
    }
    return nnew;
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

  typedef std::complex<short> CriticalPointType;

  MoleculeAcquireFileQTAIM();
  ~MoleculeAcquireFileQTAIM() override;

private:
  MoleculeAcquireFileQTAIM(const MoleculeAcquireFileQTAIM &) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileQTAIM &) VTK_DELETE_FUNCTION;

  vtkIdType NumberOfOrbitals_;
  vtkIdType NumberOfPrimitives_;
  vtkIdType CriticalPoints[NumberOfCPTypes];
};

#endif // !MoleculeAcquire_FileQTAIM_h
