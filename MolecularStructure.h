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

  vtkMolecule* getMolecule() const {return static_cast<vtkMolecule *>(molecule_);}
  operator vtkMolecule *() const { return static_cast<vtkMolecule *>(molecule_); }
  vtkMolecule *operator->() const { return this->getMolecule(); }

//  const vtkMolecule* getMolecule() const {return static_cast<vtkMolecule *>(the_molecule_);}
//  operator const vtkMolecule *() const { return static_cast<const vtkMolecule *>(the_molecule_); }
//  const vtkMolecule *operator->() const { this->getMolecule(); }

private:
  vtkNew<vtkMolecule> molecule_;
};

#endif // Molecular_Structure_h
