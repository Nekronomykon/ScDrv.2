#ifndef MoleculeAcquire_File_WFX_h
#define MoleculeAcquire_File_WFX_h

/*=========================================================================
  Program:   Local Fork of the Visualization Toolkit (VTK) C++ Part
  Module:    MoleculeAcquireFileWFX.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileWFX
 * @brief   read wavefunction .wfx files
 *
 * MoleculeAcquireFileWFX is a source object that reads waefunction files
 * This format is intentionally specified as a single-structure one.
 * The WFX file resembles XML in its syntax:
 * http://aim.tkgristmill.com/wfxformat.html
 *
 * NOT YET FINALLY RELEASED!
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
#include "MoleculeAcquireFileQM.h"
#include "ImplReadFile.h"
#include "TraitsAcquireAtoms.h"

class vtkMolecule;


namespace vtk
{

class MoleculeAcquireFileWFX
    : public ImplReadFile<MoleculeAcquireFileWFX, TraitsReadStructureMarkup, MoleculeAcquireFileQM>
{
  typedef TraitsReadStructureMarkup<MoleculeAcquireFileWFX> Traits;

public:
  static MoleculeAcquireFileWFX *New();
  vtkTypeMacro(MoleculeAcquireFileWFX, MoleculeAcquireFileQM);
  // void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

  typedef Traits::BaseInput BaseInput;
  int ParseStreamInfo(BaseInput &, vtkInformationVector *);
  int ReadSimpleMolecule(BaseInput &, Molecule *);

protected:
  explicit MoleculeAcquireFileWFX() = default;
  ~MoleculeAcquireFileWFX() override = default;

private:
  MoleculeAcquireFileWFX(const MoleculeAcquireFileWFX &) = delete;
  void operator=(const MoleculeAcquireFileWFX &) = delete;

  private:
  std::string bufAtomNumbers_;
  std::string bufAtomCoords_;
  std::string bufAtomLabels_;
};

}; // namespace vtk

#endif // !MoleculeAcquire_File_WFX_h
