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
#include "ImplReadFile.h"
#include "TraitsAcquireAtoms.h"

class vtkMolecule;

class MoleculeAcquireFileMGP
  : public ImplReadFile< MoleculeAcquireFileMGP, TraitsLabelNumberXYZ>
{
  // typedef  ImplReadFile< MoleculeAcquireFileMGP, TraitsLabelNumberXYZ> _Base;
  typedef TraitsLabelNumberXYZ<MoleculeAcquireFileMGP> Traits;
public:
  typedef Traits::BaseInput BaseInput;
  static MoleculeAcquireFileMGP *New();
  vtkTypeMacro(MoleculeAcquireFileMGP, MoleculeAcquireFile);
  // void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

  int PreParseStream(BaseInput&);
  int ReadSimpleMolecule(BaseInput&, vtkMolecule*);

protected:
  explicit MoleculeAcquireFileMGP() = default;
  ~MoleculeAcquireFileMGP() override = default;

  //int RequestData(vtkInformation *, vtkInformationVector **,
  //  vtkInformationVector *) override;

  //int RequestInformation(vtkInformation *, vtkInformationVector **,
  //  vtkInformationVector *) override;

private:
  MoleculeAcquireFileMGP(const MoleculeAcquireFileMGP&) = delete;
  void operator=(const MoleculeAcquireFileMGP&) = delete;
};


#endif // !MoleculeAcquire_FileMGP