#ifndef CriticalPointStructure_h
#define CriticalPointStructure_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkObject.h>
#include <vtkObjectFactory.h>

#include <vtkPoints.h>
#include <vtkMolecule.h>

#include <vtkSmartPointer.h>
#include <vtkNew.h>

class vtkPoints;
class vtkMolecule;

typedef vtkNew<vtkMolecule> Molecule;
// typedef vtkSmartPointer<vtkMolecule> Molecule;

class CriticalPoints
: public vtkPoints
{
public:
  static CriticalPoints* New();
  vtkTypeMacro(CriticalPoints,vtkPoints)
  void PrintSelf(ostream &os, vtkIndent indent) override;
  void Initialize() override;

  //accessor
  vtkMolecule* GetMolecule() const {return molecule_;}

protected:
  explicit CriticalPoints() = default;
  ~CriticalPoints() override = default;

private:
  CriticalPoints(const CriticalPoints &) = delete;
  void operator=(const CriticalPoints &) = delete;

private:
  Molecule molecule_;

};

#endif // !CriticalPointStructure_h
