#ifndef Molecule_Cycle__h
#define Molecule_Cycle__h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro

class vtkMolecule;
class vtkVector3d;

namespace vtk
{

class MoleculeCycle
{
private:
  vtkVector3d xyzCenter_;
  vtkVector3d xyzReperX_;
  vtkVector3d xyzReperY_;
  vtkVector3d xyzReperZ_;

public:
  MoleculeCycle(/* args */);
  ~MoleculeCycle();
};

}; // namespace vtk

#endif // !Molecule_Cycle__h