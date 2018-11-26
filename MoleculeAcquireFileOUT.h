#ifndef MoleculeAcquireFileOUT_h
#define MoleculeAcquireFileOUT_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork Copy
  Module:    MoleculeAcquireFileOUT.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileXYZ
 * @brief   MOPAC output (*.out) files
 *
 * MoleculeAcquireFileXYZ is a source object that reads MOPAC OUT files 
 *
 * NB: This reader class will never detect multiple timesteps in a single
 * XYZ molecule file, as it was assumed in the original VTK XYZ Molecule reader,
 * since the XYZ format file is initially specified as a single-structure one.
 * The Multistep Readers hierarchy is here begins from the (yet unwrit and even
 * clearly unformulated) MoleculeAcquireTrajectory class
 *
 * @par Thanks:
 * ScrewDriver te Blackheadborough who developed and contributed this class
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER
#include "MoleculeAcquireFile.h"
#include "ImplReadFile.h"
#include "TraitsAcquireAtoms.h"


class MoleculeAcquireFileOUT
    : public ImplReadFile<MoleculeAcquireFileOUT, TraitsNSymbolicXYZ, MoleculeAcquireFile>
{
  typedef ImplReadFile<MoleculeAcquireFileOUT, TraitsNSymbolicXYZ, MoleculeAcquireFile> _Base;

protected:
  typedef TraitsNSymbolicXYZ<MoleculeAcquireFileOUT> Traits;
  typedef MoleculeAcquireFile::Molecule Molecule;

public:
  static MoleculeAcquireFileOUT *New();
  vtkTypeMacro(MoleculeAcquireFileOUT, MoleculeAcquireFile);

  typedef Traits::BaseInput BaseInput;
  int PreParseStream(BaseInput &);
  int ReadSimpleMolecule(BaseInput &, Molecule *);

protected:
  MoleculeAcquireFileOUT() = default;
  ~MoleculeAcquireFileOUT() override = default;

private:
  MoleculeAcquireFileOUT(const MoleculeAcquireFileOUT &) = delete;
  void operator=(const MoleculeAcquireFileOUT &) = delete;
};

#endif // !MoleculeAcquireFileOUT_h
