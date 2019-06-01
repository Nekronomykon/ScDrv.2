#include "MoleculeMapperStyle.h"

#include <vtkMoleculeMapper.h>

using namespace vtk;

void MoleculeMapperStyle::SetupMoleculeMapper(vtkMoleculeMapper *pmap) const
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
