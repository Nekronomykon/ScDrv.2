#ifndef Field_Eval__h
#define Field_Eval__h

/**
 * FieldEval.h --- base class for field value calculations
 * 
 * The instances of this class heirs are intended to be static singletones
 * to denote, what field is used here. Should I use the vtkAlgorithm class 
 * inherently or use this class an the interface in the new hierarchy?
 * 
 */

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

class FieldEval
{
protected:
  explicit FieldEval() = default;
  virtual ~FieldEval() = default;


};

#endif //!Field_Eval__h