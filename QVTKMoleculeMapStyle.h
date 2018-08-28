#ifndef VTKMOLMAPPERSTYLE_H
#define VTKMOLMAPPERSTYLE_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkMoleculeMapper.h>

struct QVTKMoleculeMapStyle
{
  // atoms
  bool bRenderAtoms_;        //
  short styleAtomRadius_;
  float radAtomsScale_;
  // bonds
  bool bRenderBonds_;
  bool bRenderMulti_;
  short styleBondColor_;
  float radBonds_;

  //////////////////////////////////////////////////////////////////////////
  //
  void SetupMoleculeMapper(vtkMoleculeMapper* pmap) const;

  // Why don't we rely upon the default behaviour?
  //
  bool operator ==(const QVTKMoleculeMapStyle& v) const
  {
    return bool( (styleAtomRadius_ == v.styleAtomRadius_)
      && (radAtomsScale_ == v.radAtomsScale_)
      && (styleBondColor_ == v.styleBondColor_)
      && (bRenderMulti_ == v.bRenderMulti_)
      && (radBonds_ == v.radBonds_)
      );
  }
};

#endif // VTKMOLMAPPERSTYLE_H
