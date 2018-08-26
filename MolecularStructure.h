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
#include <vtkMolecule.h>

#include "BondsetBuild.h"

#include <deque>

typedef std::pair<vtkIdType,vtkIdType> IncidenceIndex;
typedef std::deque<IncidenceIndex> PathSequence;

class MolecularStructure
{
  typedef vtkSmartPointer<BondsetBuild> BuildBonds;
  typedef vtkSmartPointer<vtkMolecule> Molecule;
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

  vtkStdString GetTitle() const;
  vtkStdString ResetTitle(vtkStdString title = vtkStdString());

private:
  vtkStdString title_;
  Molecule molecule_;
  BuildBonds bonds_build_;
};

#endif // Molecular_Structure_h
