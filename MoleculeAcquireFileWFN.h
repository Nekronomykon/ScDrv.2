#ifndef MoleculeAcquire_File_WFN_h
#define MoleculeAcquire_File_WFN_h

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireFileWFN.h

  Copyright (c) ScrewDriver
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileWFN
 * @brief   read wavefunction .wfn files
 *
 * MoleculeAcquireFileWFN is a source object that reads waefunction files
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

class MoleculeAcquireFileWFN
  : public MoleculeAcquireFileQTAIM
  , public TraitsCentreWFN<MoleculeAcquireFileWFN>
{
public:
  static MoleculeAcquireFileWFN *New();
  vtkTypeMacro(MoleculeAcquireFileWFN, MoleculeAcquireFileQTAIM);
  void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

  //@{
  /**
   * Get/Set the output (vtkMolecule) that the reader will fill
   */
  vtkMolecule *GetOutput();
  void SetOutput(vtkMolecule *) override;
  //@}

protected:
  MoleculeAcquireFileWFN();
  ~MoleculeAcquireFileWFN() override;

  int RequestData(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;
  int RequestInformation(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;

private:
  MoleculeAcquireFileWFN(const MoleculeAcquireFileWFN&) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileWFN&) VTK_DELETE_FUNCTION;
};

#endif // !MoleculeAcquire_File_WFN_h
