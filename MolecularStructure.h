#ifndef Molecular_Structure_h
#define Molecular_Structure_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkMolecule.h>

class MolecularStructure
{
public:
  explicit MolecularStructure();
  ~MolecularStructure();

  void Initialize();

  operator vtkMolecule* () const
  {
    return static_cast<vtkMolecule*>(the_molecule_);
  }

private:
  vtkNew<vtkMolecule> the_molecule_;
};

#endif // Molecular_Structure_h
