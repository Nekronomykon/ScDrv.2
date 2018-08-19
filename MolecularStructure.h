#ifndef Molecular_Structure_h
#define Molecular_Structure_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkType.h>
#include <vtkStdString.h>

#include "BondsetBuild.h"

#include <vtkMolecule.h>

class MolecularStructure
{
  typedef vtkSmartPointer<BondsetBuild> BuildBonds;
  typedef vtkNew<vtkMolecule> A_Molecule;
public:
  enum Units
  {
    Bohrs,
    Angstroms,
    Picometers
  };


  explicit MolecularStructure();
  ~MolecularStructure();

  vtkMolecule* Initialize();

  vtkMolecule *getMolecule() const;
  operator vtkMolecule *() const;
  vtkMolecule *operator->() const;

  vtkIdType UpdateBonds();

  //  const vtkMolecule* getMolecule() const {return static_cast<vtkMolecule *>(the_molecule_);}
  //  operator const vtkMolecule *() const { return static_cast<const vtkMolecule *>(the_molecule_); }
  //  const vtkMolecule *operator->() const { this->getMolecule(); }



  vtkStdString GetTitle() const;
  vtkStdString ResetTitle(vtkStdString title = vtkStdString());

private:
  vtkStdString title_;
  A_Molecule molecule_;
  BuildBonds bonds_build_;
};

#endif // Molecular_Structure_h
