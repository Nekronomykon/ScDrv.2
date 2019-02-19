#ifndef CriticalPointStructure_h
#define CriticalPointStructure_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkMolecule.h>

#include <vtkSmartPointer.h>
#include <vtkNew.h>

class vtkPoints;

namespace vtk
{

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ CriticalPointStructure
    : public vtkMolecule
{

public:
  static CriticalPointStructure *New();
  vtkTypeMacro(CriticalPointStructure, vtkMolecule);
  void PrintSelf(ostream &os, vtkIndent indent) override;
  void Initialize() override;

protected:
  CriticalPointStructure() = default;
  ~CriticalPointStructure() override = default;

private:
  vtkNew<vtkPoints> points_;
};

}; // namespace vtk

#endif // !CriticalPointStructure_h
