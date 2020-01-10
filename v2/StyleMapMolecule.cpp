#include <vtkMoleculeMapper.h>

#include <algorithm>
#include <utility>

#include "StyleMapMolecule.h"
using namespace vtk;

static inline bool operator==(const StyleMapMolecule &w, const StyleMapMolecule &v)
{
  return bool(
    (w.styleAtomRadius_ == v.styleAtomRadius_) 
  && (w.radAtomsScale_ == v.radAtomsScale_) 
  && (w.styleBondColor_ == v.styleBondColor_) 
  && (w.bRenderMulti_ == v.bRenderMulti_) && (w.radBonds_ == v.radBonds_) 
  && (w.colorBond_[0] == v.colorBond_[0]) && (w.colorBond_[1] == v.colorBond_[1]) && (w.colorBond_[2] == v.colorBond_[2])
  );
}

static inline bool operator!=(const StyleMapMolecule &w, const StyleMapMolecule &v)
{
  return bool(
    (w.styleAtomRadius_ != v.styleAtomRadius_) 
  || (w.radAtomsScale_ != v.radAtomsScale_) 
  || (w.styleBondColor_ != v.styleBondColor_) 
  || (w.bRenderMulti_ != v.bRenderMulti_) || (w.radBonds_ != v.radBonds_) 
  || (w.colorBond_[0] != v.colorBond_[0]) || (w.colorBond_[1] != v.colorBond_[1]) || (w.colorBond_[2] != v.colorBond_[2])
  );
}


void StyleMapMolecule::SetupMoleculeMapper(vtkMoleculeMapper *pmap) const
{
  // atoms
  pmap->SetRenderAtoms(true);
  pmap->SetAtomicRadiusType(styleAtomRadius_);
  pmap->SetAtomicRadiusScaleFactor(radAtomsScale_);
  // bonds
  pmap->SetRenderBonds(bRenderBonds_);
  pmap->SetBondColorMode(styleBondColor_);
  pmap->SetUseMultiCylindersForBonds(bRenderMulti_);
  pmap->SetBondRadius(radBonds_);
  pmap->SetBondColor(colorBond_[0], colorBond_[1], colorBond_[2]);
}
