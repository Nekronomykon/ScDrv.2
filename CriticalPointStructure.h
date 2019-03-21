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

class CriticalPointStructure
: public vtkPoints
{

public:
  static CriticalPointStructure* New();
  vtkTypeMacro(CriticalPointStructure,vtkPoints)
  void PrintSelf(ostream &os, vtkIndent indent) override;
  void Initialize() override;

protected:
  CriticalPointStructure() = default;
  ~CriticalPointStructure() override = default;

private:
  vtkSmartPointer<vtkMolecule> molecule_;
  // vtkNew<vtkPoints> points_;
};

#endif // !CriticalPointStructure_h
