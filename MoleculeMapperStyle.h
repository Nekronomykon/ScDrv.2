#ifndef MoleculeMapper_Style_h
#define MoleculeMapper_Style_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkColor.h>

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
  unsigned char colorBond_[3]; // transform to color4?

public:
  //////////////////////////////////////////////////////////////////////////
  //
  bool HasToRenderAtoms() const { return bRenderAtoms_; }
  bool RenderAtomsOn() { bRenderAtoms_ = true; }
  bool RenderAtomsOff() { bRenderAtoms_ = false; }
  bool ToggleRenderAtoms() { bRenderAtoms_ = !bRenderAtoms_; }
  //
  short GetTypeAtomicRadius() const { return styleAtomRadius_; }
  short ResetAtomicRadiusType(short rad_type)
  {
    std::swap(rad_type, styleAtomRadius_);
    return rad_type;
  }
  //
  float GetAtomicRadiusScale() const
  {
    return radAtomsScale_;
  }
  float ResetAtomicRadiusScale(float sc)
  {
    std::swap(sc, radAtomsScale_);
    return sc;
  }
  //
  bool HasToRenderBonds() const { return bRenderBonds_; }
  void RenderBondsOn() { bRenderBonds_ = true; }
  void RenderBondsOff() { bRenderBonds_ = false; }
  void ToggleRenderBonds() { bRenderBonds_ = !bRenderBonds_; }
  //
  bool IsMultiBonds() const { return bRenderMulti_; }
  bool MultiBondsOn() { bRenderMulti_ = true; }
  bool MultiBondsOff() { bRenderMulti_ = false; }
  bool ToggleMultiBonds() { bRenderMulti_ = !bRenderMulti_; }
  //
  short GetTypeBondsColor() const { return styleBondColor_; }
  short ResetTypeBondsColor(short col_type)
  {
    std::swap(col_type, styleBondColor_);
    return col_type;
  }
  //
  float GetBondRadius() const { return radBonds_; }
  float ReserBondRadius(float rb)
  {
    std::swap(rb, radBonds_);
    return rb;
  }
  //
  //////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////
  //
  void SetupMoleculeMapper(MoleculeMapper* pmap) const;

  // Why don't we rely upon the default behaviour?
  //
  bool operator ==(const MoleculeMapperStyle& v) const
  {
    return bool((styleAtomRadius_ == v.styleAtomRadius_)
      && (radAtomsScale_ == v.radAtomsScale_)
      && (styleBondColor_ == v.styleBondColor_)
      && (bRenderMulti_ == v.bRenderMulti_)
      && (radBonds_ == v.radBonds_)
      //&& (colorBond_[0] == v.colorBond_[0])
      //&& (colorBond_[1] == v.colorBond_[1])
      //&& (colorBond_[2] == v.colorBond_[2])
      );
  }
  //
  //////////////////////////////////////////////////////////////////////////
};

#endif // MoleculeMapper_Style_h
