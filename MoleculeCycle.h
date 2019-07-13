#ifndef Molecule_Cycle__h
#define Molecule_Cycle__h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro

#include <vtkVector.h> // Small templated vector convenience class

class vtkMolecule;
class vtkVector3d;
class vtkMatrix3x3;
class vtkMatrix4x4;

namespace vtk
{

class MoleculeCycle
{
private:
  vtkVector3d xyzCenter_;
  // vtkMatrix3x3 reper_;

public:
  MoleculeCycle(/* args */);
  ~MoleculeCycle() = default;
};

}; // namespace vtk

#endif // !Molecule_Cycle__h