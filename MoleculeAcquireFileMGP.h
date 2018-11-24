#ifndef MoleculeAcquire_FileMGP
#define MoleculeAcquire_FileMGP

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireFileMGP.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileMGP
 * @brief   read wavefunction .wfn files
 *
 * MoleculeAcquireFileMGP is for the result files from the AIMAll calcutaions
 * This format is specified as a single-structure one.
 *
 * NOT YET FINALLY RELEASED!
 *
 * @par Thanks:
 * ScrewDriver te Blackheadborough who developed and contributed this class
 * NB: It is preconverted from the MoleculeAcquireFileWFN class
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

class MoleculeAcquireFileMGP
  : public MoleculeAcquireFileQTAIM
  , public TraitsLabelNumberXYZ<MoleculeAcquireFileMGP>
{
public:
  static MoleculeAcquireFileMGP *New();
  vtkTypeMacro(MoleculeAcquireFileMGP, MoleculeAcquireFileQTAIM);
  void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

  //@{
  /**
   * Get/Set the output (vtkMolecule) that the reader will fill
   */
  vtkMolecule *GetOutput();
  void SetOutput(vtkMolecule *) override;
  //@}

protected:
  MoleculeAcquireFileMGP() = default;
  ~MoleculeAcquireFileMGP() override = default;

  int RequestData(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;
  int RequestInformation(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;

private:
  MoleculeAcquireFileMGP(const MoleculeAcquireFileMGP&) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileMGP&) VTK_DELETE_FUNCTION;
};


#endif // !MoleculeAcquire_FileMGP