#ifndef MoleculeAcquire_FileARC_h
#define MoleculeAcquire_FileARC_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork Copy
  Module:    MoleculeAcquireFileARC.h

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
 * MoleculeAcquireFileARC is a source object that reads MOPAC OUT files
 *
 * NB: This reader class will never detect multiple timesteps in a file
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

class MoleculeAcquireFileARC
    : public MoleculeAcquireFile,
      public TraitsSymXYZPadded<MoleculeAcquireFileARC>
{
protected:
  typedef MoleculeAcquireFile::Molecule Molecule;
  typedef TraitsSymXYZPadded<MoleculeAcquireFileARC> Traits;

public:
  static MoleculeAcquireFileARC *New();
  vtkTypeMacro(MoleculeAcquireFileARC, MoleculeAcquireFile);
  void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
  MoleculeAcquireFileARC();
  ~MoleculeAcquireFileARC() override;

public:
  int RequestInformation(vtkInformation *, vtkInformationVector **,
                         vtkInformationVector *) override;

  int RequestData(vtkInformation *, vtkInformationVector **,
                  vtkInformationVector *) override;

private:
  MoleculeAcquireFileARC(const MoleculeAcquireFileARC &) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileARC &) VTK_DELETE_FUNCTION;
};

#endif // !MoleculeAcquire_FileARC_h
