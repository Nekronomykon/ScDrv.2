#ifndef MoleculeAcquire_FileEXTOUT
#define MoleculeAcquire_FileEXTOUT

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireFileEXTOUT.h

  Copyright (c) ScrewDriver
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileEXTOUT
 * @brief   read molecular graph .mgp files from AIMAll
 *
 * MoleculeAcquireFileEXTOUT is a source object that reads waefunction files
 * This format is intentionally specified as a single-structure one.
 *
 * NOT YET FINALLY RELEASED!
 *
 * @par Thanks:
 * ScrewDriver de Blackheadborough who developed and contributed this class
 * NB: It is preconverted from the MoleculeAcquireFileXYZ class
 * and yet not in its final executive form.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireFileQTAIM.h"

#include "TraitsAcquireAtoms.h"

class vtkMolecule;

class MoleculeAcquireFileEXTOUT
  : public MoleculeAcquireFileQTAIM
  , public TraitsCentreWFN<MoleculeAcquireFileEXTOUT>
{
public:
  static MoleculeAcquireFileEXTOUT *New();
  vtkTypeMacro(MoleculeAcquireFileEXTOUT, MoleculeAcquireFileQTAIM);
  void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

  //@{
  /**
   * Get/Set the output (vtkMolecule) that the reader will fill
   */
  vtkMolecule *GetOutput();
  void SetOutput(vtkMolecule *) override;
  //@}

protected:
  MoleculeAcquireFileEXTOUT();
  ~MoleculeAcquireFileEXTOUT() override;

  int RequestData(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;
  int RequestInformation(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;

private:
  MoleculeAcquireFileEXTOUT(const MoleculeAcquireFileEXTOUT&) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileEXTOUT&) VTK_DELETE_FUNCTION;
};



#endif // !MoleculeAcquire_FileEXTOUT