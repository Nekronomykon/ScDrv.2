#ifndef __MoleculeAcquireFileXYZ_h__
#define __MoleculeAcquireFileXYZ_h__

/*=========================================================================

  Program:   Visualization Toolkit Local Fork Copy
  Module:    MoleculeAcquireFileXYZ.h

  Copyright (c) ScrewDriver de Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileXYZ
 * @brief   read XMol .xyz files
 *
 * MoleculeAcquireFileXYZ is a source object that reads XMol XYZ files of extended
 * format.
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

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireFile.h"

#include "TraitsAcquireAtoms.h"

class vtkMolecule;

class MoleculeAcquireFileXYZ
  : public MoleculeAcquireFile
  , public TraitsSymbolicXYZ<MoleculeAcquireFileXYZ>
{
protected:
  typedef MoleculeAcquireFile::Molecule Molecule;

public:
  static MoleculeAcquireFileXYZ *New();
  vtkTypeMacro(MoleculeAcquireFileXYZ, MoleculeAcquireFile);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;


protected:
  MoleculeAcquireFileXYZ();
  ~MoleculeAcquireFileXYZ() VTK_OVERRIDE;

  int RequestData(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) VTK_OVERRIDE;
  int RequestInformation(vtkInformation *, vtkInformationVector **,
    vtkInformationVector *) VTK_OVERRIDE;

private:
  MoleculeAcquireFileXYZ(const MoleculeAcquireFileXYZ&) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileXYZ&) VTK_DELETE_FUNCTION;
};

#endif // !__MoleculeAcquireFileXYZ_h__
