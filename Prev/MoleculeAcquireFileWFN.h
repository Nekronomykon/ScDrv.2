#ifndef MoleculeAcquire_File_WFN_h
#define MoleculeAcquire_File_WFN_h

/*=========================================================================
  Program:   Local Fork of the Visualization Toolkit (VTK) C++ Part
  Module:    MoleculeAcquireFileWFN.h

  Copyright (c) ScrewDriver te Blackheadborough
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
 * CLOSE TO THE FINAL FORM!
 *
 * @par Thanks:
 * ScrewDriver te Blackheadborough who developed and contributed this class
 * NB: Here it is not yet in its final executive form.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireFileField.h"
#include "ImplReadFile.h"
#include "TraitsAcquireAtoms.h"


namespace vtk
{

  class MoleculeAcquireFileWFN
    : public ImplReadFile<MoleculeAcquireFileWFN, TraitsCentreWFN, MoleculeAcquireFileField>
  {
    typedef TraitsCentreWFN<MoleculeAcquireFileWFN> Traits;
  public:
    static MoleculeAcquireFileWFN *New();
    vtkTypeMacro(MoleculeAcquireFileWFN, MoleculeAcquireFileField);
    // void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

    int ParseStreamInfo(BaseInput&,vtkInformationVector*);
    int ReadMolecule(std::istream&, vtkMolecule*) override;

  protected:
    explicit MoleculeAcquireFileWFN() = default;
    ~MoleculeAcquireFileWFN() override = default;

  private:
    MoleculeAcquireFileWFN(const MoleculeAcquireFileWFN&) = delete;
    void operator=(const MoleculeAcquireFileWFN &) = delete;
  };

}; // namespace vtk

#endif // !MoleculeAcquire_File_WFN_h
