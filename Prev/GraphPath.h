#ifndef Graph_Path_h
#define Graph_Path_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkType.h>
#include <vtkMolecule.h>
#include <vtkIdTypeArray.h>

// template<class TGraph>
class GraphPath
{
public:
  explicit GraphPath();
  ~GraphPath(); // override;

private:
  vtkNew<vtkIdTypeArray> vertices_;
  vtkNew<vtkIdTypeArray> egdes_;
};

#endif // !Graph_Path_h
