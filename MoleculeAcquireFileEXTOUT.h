#ifndef MoleculeAcquire_FileEXTOUT
#define MoleculeAcquire_FileEXTOUT

/*=========================================================================

  Program:   Local Fork of the Visualization Toolkit (VTK) C++ Part
  Module:    MoleculeAcquireFileEXTOUT.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileEXTOUT
 * @brief   read molecular graph .mgp files from AIMAll
 *
 * MoleculeAcquireFileEXTOUT is is for the result files from the AIMAll calcutaions
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

namespace vtk
{

  class MoleculeAcquireFileEXTOUT
    : public ImplReadFile<MoleculeAcquireFileEXTOUT, TraitsSymbolicXYZ, MoleculeAcquireFileQTAIM>
  {
    typedef ImplReadFile<MoleculeAcquireFileEXTOUT, TraitsSymbolicXYZ, MoleculeAcquireFileQTAIM> _Base;
    typedef TraitsSymbolicXYZ<MoleculeAcquireFileEXTOUT> Traits;
  public:
    typedef Traits::BaseInput BaseInput;
    typedef typename _Base::Molecule Molecule;
    static MoleculeAcquireFileEXTOUT *New();
    vtkTypeMacro(MoleculeAcquireFileEXTOUT, MoleculeAcquireFileQTAIM);
    // void PrintSelf(ostream& /*os*/, vtkIndent /*indent*/) override;

    int PreParseStream(BaseInput&);
    int ReadSimpleMolecule(BaseInput&, Molecule*);

  protected:
    explicit MoleculeAcquireFileEXTOUT() = default;
    ~MoleculeAcquireFileEXTOUT() override = default;

  private:
    MoleculeAcquireFileEXTOUT(const MoleculeAcquireFileEXTOUT&) VTK_DELETE_FUNCTION;
    void operator=(const MoleculeAcquireFileEXTOUT&) VTK_DELETE_FUNCTION;
  };

}; // namespace vtk

#endif // !MoleculeAcquire_FileEXTOUT