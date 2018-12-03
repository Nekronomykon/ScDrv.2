#ifndef MoleculeAcquire_File_CUBE_h
#define MoleculeAcquire_File_CUBE_h

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireFileCUBE.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireFileCUBE
 * @brief   Reads a Gaussian Cube file;
 * output a vtkMolecule object and a vtkImageData of field values
 *
 * NOT YET FINISHED!
 *
 * @par Thanks:
 * ScrewDriver te Blackheadborough who is trying to rewrite this class
 * NB: It is preconverted from the original VTK CUBE file reader class
 * and yet not in its final executive form.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include "MoleculeAcquireFile.h"

class vtkMolecule;
class vtkImageData;

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MoleculeAcquireFileCUBE
    : public MoleculeAcquireFile
{
public:
  static MoleculeAcquireFileCUBE *New();
  vtkTypeMacro(MoleculeAcquireFileCUBE, MoleculeAcquireFile)
  void PrintSelf(ostream &os, vtkIndent indent) override;

  /**
   * Get/Set the output (vtkImageData) that the reader will fill
   */
  vtkImageData *GetGridOutput();

protected:
  MoleculeAcquireFileCUBE();
  ~MoleculeAcquireFileCUBE() override = default;

  int RequestData(vtkInformation *, vtkInformationVector **,
                  vtkInformationVector *) override;
  int RequestInformation(vtkInformation *, vtkInformationVector **,
                         vtkInformationVector *) override;
  int FillOutputPortInformation(int, vtkInformation *) override;

private:
  MoleculeAcquireFileCUBE(const MoleculeAcquireFileCUBE &) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireFileCUBE &) VTK_DELETE_FUNCTION;
};

#endif // !MoleculeAcquire_File_CUBE_h
