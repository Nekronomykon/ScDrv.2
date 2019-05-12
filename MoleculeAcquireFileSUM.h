#ifndef MoleculeAcquireFileSUM_h
#define MoleculeAcquireFileSUM_h

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireFileSUM.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileSUM
 * @brief   read wavefunction .wfn files
 *
 * MoleculeAcquireFileSUM is for the result files from the AIMAll calcutaions
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

namespace vtk
{

  class MoleculeAcquireFileSUM
    : public ImplReadFile<MoleculeAcquireFileSUM, TraitsLabelNumberXYZ, MoleculeAcquireFileQTAIM>
  {
    typedef ImplReadFile<MoleculeAcquireFileSUM, TraitsLabelNumberXYZ, MoleculeAcquireFileQTAIM> _Base;
    typedef TraitsLabelNumberXYZ<MoleculeAcquireFileSUM> Traits;
  public:

    static MoleculeAcquireFileSUM *New();
    vtkTypeMacro(MoleculeAcquireFileSUM, MoleculeAcquireFile);
    // void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

    int ParseStreamInfo(BaseInput&,vtkInformationVector*);
    int ReadMolecule(std::istream &, vtkMolecule *) override;

  protected:
    explicit MoleculeAcquireFileSUM() = default;
    ~MoleculeAcquireFileSUM() override = default;

  private:
    MoleculeAcquireFileSUM(const MoleculeAcquireFileSUM&) = delete;
    void operator=(const MoleculeAcquireFileSUM&) = delete;
  };

}; // namespace vtk

#endif // !MoleculeAcquire_FileSUM