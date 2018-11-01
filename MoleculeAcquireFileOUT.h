#ifndef MoleculeAcquire_FileOUT_h
#define MoleculeAcquire_FileOUT_h

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

#include "TraitsAcquireAtoms.h"

#include "MoleculeAcquireFile.h"

class MoleculeAcquireFileOUT
  : public MoleculeAcquireFile
  , public TraitsNSymbolicXYZ<MoleculeAcquireFileOUT>

{
protected:
  typedef MoleculeAcquireFile::Molecule Molecule;

public:
  static MoleculeAcquireFileOUT *New();
  vtkTypeMacro(MoleculeAcquireFileOUT, MoleculeAcquireFile);
  void PrintSelf(ostream& os, vtkIndent indent) override;


protected:
  MoleculeAcquireFileOUT();
  virtual ~MoleculeAcquireFileOUT();

  typedef TraitsNSymbolicXYZ<MoleculeAcquireFileOUT> Traits;

  int RequestInformation(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;

  int RequestData(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) override;

private:
  MoleculeAcquireFileOUT(const MoleculeAcquireFileOUT&) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileOUT&) VTK_DELETE_FUNCTION;
};

#endif // !MoleculeAcquire_FileOUT_h
