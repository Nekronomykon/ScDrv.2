#ifndef __Read_MoleculeFile_Base_h
#define __Read_MoleculeFile_Base_h

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkMoleculeAlgorithm.h>

#include <vtkMoleculeReaderBase.h>

namespace vtk {

typedef vtkMoleculeAlgorithm ReadMoleculeFileBase;

typedef vtkMoleculeReaderBase ReadMoleculeFileBase2;
};

#endif //!__Read_MoleculeFile_Base_h
