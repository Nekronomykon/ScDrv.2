#ifndef MoleculeMapper_Style_h
#define MoleculeMapper_Style_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

class MoleculeMapper;

struct MoleculeMapperStyle
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
  unsigned char colorBond_[3];

  //////////////////////////////////////////////////////////////////////////
  //
  void SetupMoleculeMapper(MoleculeMapper* pmap) const;

  // Why don't we rely upon the default behaviour?
  //
  bool operator ==(const MoleculeMapperStyle& v) const
  {
    return bool( (styleAtomRadius_ == v.styleAtomRadius_)
      && (radAtomsScale_ == v.radAtomsScale_)
      && (styleBondColor_ == v.styleBondColor_)
      && (bRenderMulti_ == v.bRenderMulti_)
      && (radBonds_ == v.radBonds_)
      && (colorBond_[0] == v.colorBond_[0])
      && (colorBond_[1] == v.colorBond_[1])
      && (colorBond_[2] == v.colorBond_[2])
      );
  }
};

#endif // MoleculeMapper_Style_h
