#ifndef __Read_MoleculeFile_XYZ_h
#define __Read_MoleculeFile_XYZ_h

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkXYZMolReader2.h>

#include "ReadMoleculeFileBase.h"

namespace vtk {
typedef vtkXYZMolReader2 ReadMoleculeFileXYZ;
};

#endif //!__Read_MoleculeFile_XYZ_h
