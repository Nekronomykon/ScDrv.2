#ifndef CriticalPoints_h
#define CriticalPoints_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkSmartPointer.h>
#include <vtkNew.h>

#include <vtkUndirectedGraph.h>

class vtkPoints;
class vtkFloatArray;
class vtkMolecule;

typedef vtkSmartPointer<vtkMolecule> Molecule;
typedef vtkNew<vtkMolecule> NewMolecule;

typedef vtkSmartPointer<vtkFloatArray> Values;
typedef vtkNew<vtkFloatArray> NewValues;

typedef vtkSmartPointer<vtkPoints> Points;
typedef vtkNew<vtkPoints> NewPoints;

// a type token:
#define SCDRV_CRITICAL_POINTS 88

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

protected:
  explicit CriticalPoints() = default;
  ~CriticalPoints() override = default;

public:
  void Initialize() override;

  /**
   * Return what type of dataset this is.
   */
  int GetDataObjectType() override { return SCDRV_CRITICAL_POINTS; }

  //accessor
  vtkMolecule *GetMolecule() const { return molecule_; }

  vtkPoints *Points() const;

private:
  CriticalPoints(const CriticalPoints &) = delete;
  void operator=(const CriticalPoints &) = delete;

private:
  NewMolecule molecule_;

  NewPoints points_;

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
