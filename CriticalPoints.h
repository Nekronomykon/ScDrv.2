#ifndef CriticalPoints_h
#define CriticalPoints_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkObject.h>
#include <vtkObjectFactory.h>

#include <vtkPoints.h>
#include <vtkUndirectedGraph.h>
#include <vtkMolecule.h>
#include <vtkFloatArray.h>

#include <vtkSmartPointer.h>
#include <vtkNew.h>

class vtkFloatArray;
class vtkMolecule;

typedef vtkNew<vtkMolecule> NewMolecule;
typedef vtkSmartPointer<vtkMolecule> Molecule;

typedef vtkSmartPointer<vtkFloatArray> Values;
typedef vtkNew<vtkFloatArray> NewValues;

typedef vtkNew<vtkPoints> NewPoints;

class CriticalPoints
    : public vtkUndirectedGraph
{
public:
  enum
  {
    AtomMaximumCP = 0,
    BondSaddleCP = 1,
    RingSaddleCP = 2,
    CageMinimumCP = 3,
    NonNuclearMaxCP = 4,
    NumberOfCPTypes = 5
  };


  static CriticalPoints *New();
  vtkTypeMacro(CriticalPoints, vtkUndirectedGraph);
  void PrintSelf(ostream &os, vtkIndent indent) override;
  void Initialize() override;

  //accessor
  vtkMolecule *GetMolecule() const { return molecule_; }

protected:
  explicit CriticalPoints() = default;
  ~CriticalPoints()override = default;

private:
  CriticalPoints(const CriticalPoints &) = delete;
  void operator=(const CriticalPoints &) = delete;

private:
  NewMolecule molecule_;

  vtkIdType SizesCPTypes[NumberOfCPTypes];

  // Field values:
  NewValues fieldValues_;
  // Hessian of the field:
  NewPoints eigValues_;
  NewPoints eigVectors1_;
  NewPoints eigVectors2_;
  NewPoints eigVectors3_;
  // digits as in the file format
};

#endif // !CriticalPoints_h
