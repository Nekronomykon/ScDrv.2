#ifndef MoleculeAcquireFileMGP_h
#define MoleculeAcquireFileMGP_h

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

class MoleculeAcquireFileMGP
  : public ImplReadFile<MoleculeAcquireFileMGP, TraitsLabelNumberXYZ, MoleculeAcquireFileQTAIM>
{
  typedef ImplReadFile<MoleculeAcquireFileMGP, TraitsLabelNumberXYZ, MoleculeAcquireFileQTAIM> _Base;
  typedef TraitsLabelNumberXYZ<MoleculeAcquireFileMGP> Traits;
public:
  typedef Traits::BaseInput BaseInput;
  typedef _Base::Molecule Molecule;

  static MoleculeAcquireFileMGP *New();
  vtkTypeMacro(MoleculeAcquireFileMGP, MoleculeAcquireFile);
  // void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

  int PreParseStream(BaseInput&);
  int ReadSimpleMolecule(BaseInput&, Molecule*);

protected:
  explicit MoleculeAcquireFileMGP() = default;
  ~MoleculeAcquireFileMGP() override = default;

private:
  MoleculeAcquireFileMGP(const MoleculeAcquireFileMGP&) = delete;
  void operator=(const MoleculeAcquireFileMGP&) = delete;
};


#endif // !MoleculeAcquireFileMGP_h
