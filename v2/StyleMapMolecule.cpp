#include <vtkMoleculeMapper.h>

#include <algorithm>
#include <utility>

#include "StyleMapMolecule.h"
using namespace vtk;

bool StyleMapMolecule::operator==(const StyleMapMolecule &v)const
{
  return bool((styleAtomRadius_ == v.styleAtomRadius_) 
  && (radAtomsScale_ == v.radAtomsScale_) 
  && (styleBondColor_ == v.styleBondColor_) 
  && (bRenderMulti_ == v.bRenderMulti_) && (radBonds_ == v.radBonds_) 
  && (colorBond_[0] == v.colorBond_[0]) && (colorBond_[1] == v.colorBond_[1]) && (colorBond_[2] == v.colorBond_[2])
  );
}

bool StyleMapMolecule::operator!=(const StyleMapMolecule &v)const
{
  return bool((styleAtomRadius_ != v.styleAtomRadius_) 
  || (radAtomsScale_ != v.radAtomsScale_) 
  || (styleBondColor_ != v.styleBondColor_) 
  || (bRenderMulti_ != v.bRenderMulti_) || (radBonds_ != v.radBonds_) 
  || (colorBond_[0] != v.colorBond_[0]) || (colorBond_[1] != v.colorBond_[1]) || (colorBond_[2] != v.colorBond_[2])
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
