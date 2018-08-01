#ifndef MoleculeAcquireFileWFN_h
#define MoleculeAcquireFileWFN_h

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
  void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) VTK_OVERRIDE;

  //@{
  /**
   * Get/Set the output (vtkMolecule) that the reader will fill
   */
  vtkMolecule *GetOutput();
  void SetOutput(vtkMolecule *) VTK_OVERRIDE;
  //@}

protected:
  MoleculeAcquireFileWFN();
  ~MoleculeAcquireFileWFN() VTK_OVERRIDE;

  int RequestData(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) VTK_OVERRIDE;
  int RequestInformation(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) VTK_OVERRIDE;

private:
  MoleculeAcquireFileWFN(const MoleculeAcquireFileWFN&) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileWFN&) VTK_DELETE_FUNCTION;
};

#endif
