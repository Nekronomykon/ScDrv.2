#ifndef Graph_Path_h
#define Graph_Path_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkType.h>
#include <vtkMolecule.h>

// template<class TGraph>
class GraphPath
{
public:
  explicit GraphPath();

private:
  vtkIdTypeArray vertices_;
  vtkIdTypeArray egdes_;
};

#endif // !Graph_Path_h