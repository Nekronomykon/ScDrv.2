#ifndef MoleculeMapper_Style_h
#define MoleculeMapper_Style_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkColor.h>
#include <vtkMoleculeMapper.h>

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
  enum {
    CovalentRadius = 0,
    VDWRadius,
    UnitRadius,
    CustomArrayRadius
  };
  short GetAtomicRadiusType() const { return styleAtomRadius_; }
  short ResetAtomicRadiusType(short rad_type)
  {
    std::swap(rad_type, styleAtomRadius_);
    return rad_type;
  }
  static const char* AtomRadiusModeName(short mode)
  {
    switch (mode)
    {
    case CovalentRadius:
      return "CovalentRadius";
    case VDWRadius:
      return "VDWRadius";
    case UnitRadius:
      return "UnitRadius";
    case CustomArrayRadius:
      return "CustomArrayRadius";
    default:
      return nullptr;
    }
  }
  const char * GetAtomicRadiusTypeAsString() const
  {
    const char* res = AtomRadiusModeName( this->GetAtomicRadiusType() );
    return  (!res) ? "InvalidType" : res;
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
  enum {
    SingleColor = 0,
    DiscreteByAtom
  };
  static const char* BondColorModeName(short mode)
  {
    switch (mode)
    {
    case SingleColor:
      return "SingleColor";
    case DiscreteByAtom:
      return "DiscreteByAtom";
    default:
      return nullptr;
    }
  }
  const char* GetBondColorModeAsString() const
  {
    const char* res = BondColorModeName(this->GetTypeBondsColor());
    return  (!res) ? "InvalidType" : res;
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
  // Just in case the application of the external style upon the VTK class
  // vtkMoleculeMapper
  // 
  void SetupMoleculeMapper(vtkMoleculeMapper* pmap) const;
  //
  //////////////////////////////////////////////////////////////////////////
};

static inline
bool operator ==(const MoleculeMapperStyle& w, const MoleculeMapperStyle& v)
{
  return bool((w.styleAtomRadius_ == v.styleAtomRadius_)
    && (w.radAtomsScale_ == v.radAtomsScale_)
    && (w.styleBondColor_ == v.styleBondColor_)
    && (w.bRenderMulti_ == v.bRenderMulti_)
    && (w.radBonds_ == v.radBonds_)
    && (w.colorBond_[0] == v.colorBond_[0])
    && (w.colorBond_[1] == v.colorBond_[1])
    && (w.colorBond_[2] == v.colorBond_[2])
    );
}

static inline
bool operator !=(const MoleculeMapperStyle& w, const MoleculeMapperStyle& v)
{
  return !(w  == v);
}

#endif // MoleculeMapper_Style_h
