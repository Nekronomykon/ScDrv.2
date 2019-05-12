#ifndef MoleculeAcquire_File_XYZ_h
#define MoleculeAcquire_File_XYZ_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork Copy
  Module:    MoleculeAcquireFileXYZ.h

  Copyright (c) ScrewDriver te Blackheadborough
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
#include "ImplReadFile.h"
#include "TraitsAcquireAtoms.h"

class vtkMolecule;

namespace vtk
{

  class MoleculeAcquireFileXYZ
    : public ImplReadFile<MoleculeAcquireFileXYZ, TraitsSymbolicXYZ, MoleculeAcquireFile>
  {
    typedef  ImplReadFile<MoleculeAcquireFileXYZ, TraitsSymbolicXYZ, MoleculeAcquireFile> _Base;
  protected:
    typedef MoleculeAcquireFile::Molecule Molecule;
    typedef TraitsSymbolicXYZ<MoleculeAcquireFileXYZ> Traits;
    typedef Traits::BaseInput BaseInput;

  public:
    static MoleculeAcquireFileXYZ *New();
    vtkTypeMacro(MoleculeAcquireFileXYZ, MoleculeAcquireFile);
    // void PrintSelf(ostream& os, vtkIndent indent) override;

    int ParseStreamInfo(BaseInput&,vtkInformationVector*);

    int ReadMolecule(std::istream&, vtkMolecule*) override;

  protected:
    explicit MoleculeAcquireFileXYZ() = default;
    ~MoleculeAcquireFileXYZ() override = default;

  private:
    MoleculeAcquireFileXYZ(const MoleculeAcquireFileXYZ&) = delete;
    void operator=(const MoleculeAcquireFileXYZ&) = delete;
  };


}; // namespace vtk
#endif // !MoleculeAcquire_File_XYZ_h
