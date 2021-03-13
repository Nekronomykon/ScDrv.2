#ifndef Molecular_Structure_h
#define Molecular_Structure_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkIdTypeArray.h>
#include <vtkType.h>
#include <vtkStdString.h>
#include <vtkMolecule.h>

#include "BondsetBuild.h"
using namespace vtk;

#include "GraphPath.h"
#include "CriticalPoints.h"

#include <deque>
#include <list>

using namespace std;

typedef pair<vtkIdType, vtkIdType> IncidenceIndex;
typedef deque<IncidenceIndex> PathSequence;
typedef list<PathSequence> PathPool;
typedef vtkSmartPointer<vtkIdTypeArray> IndexArray;

typedef vtkSmartPointer<BondsetBuild> BuildBonds;
typedef vtkSmartPointer<vtkMolecule> Molecule;
typedef vtkNew<vtkMolecule> NewMolecule;

typedef vtkNew<CriticalPoints> CritPoints;

class MolecularStructure
{
public:
  enum Units
  {
    Bohrs,
    Angstroms,
    Picometers
  };

  explicit MolecularStructure();
  ~MolecularStructure();

  vtkMolecule *Initialize();

  vtkMolecule *getMolecule() const;
  operator vtkMolecule *() const;
  vtkMolecule *operator->() const;

  vtkIdType UpdateBonds();

  vtkStdString GetTitle() const;
  vtkStdString ResetTitle(vtkStdString title = vtkStdString());

private:
  BuildBonds bonds_build_;
  // data
  vtkStdString title_;  
  CritPoints critical_;

  Molecule molecule_;
  IndexArray idxSelectedAtoms_;
  IndexArray idxSelectedBonds_;
  //
  PathPool paths_;
};

#endif // Molecular_Structure_h
