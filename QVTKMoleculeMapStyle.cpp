#include "QVTKMoleculeMapStyle.h"

void QVTKMoleculeMapStyle::SetupMoleculeMapper(vtkMoleculeMapper *pmap) const
{
  // atoms
  pmap->SetRenderAtoms(bRenderAtoms_);
  pmap->SetAtomicRadiusType(styleAtomRadius_);
  pmap->SetAtomicRadiusScaleFactor(radAtomsScale_);
  // bonds
  pmap->SetRenderBonds(bRenderBonds_);
  if (bRenderBonds_)
    {
      pmap->SetBondColorMode(styleBondColor_);
      pmap->SetUseMultiCylindersForBonds(bRenderMulti_);
      pmap->SetBondRadius(radBonds_);
    }
}
