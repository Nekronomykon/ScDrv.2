#include "ModelMolecularBondset.h"

ModelMolecularBondset::ModelMolecularBondset(vtkMolecule* pMol)
  : QAbstractTableModel ()
  , ptr_mol_(pMol)
  , numberOfBonds_(pMol ? pMol->GetNumberOfBonds() : 0)
{}

ModelMolecularBondset::~ModelMolecularBondset(){}

vtkMolecule *ModelMolecularBondset::resetMolecule(vtkMolecule *pNewMol)
{
  if (pNewMol != ptr_mol_) // reassign if ptr changed
    std::swap(pNewMol, ptr_mol_);
  vtkIdType nNow = !ptr_mol_ ? 0 : ptr_mol_->GetNumberOfBonds();
  if(nNow > numberOfBonds_)
  {
    beginInsertRows(QModelIndex(),numberOfBonds_,nNow - 1);
    numberOfBonds_ = nNow;
    endInsertRows();
  }
  if(nNow < numberOfBonds_)
  {
    beginRemoveRows(QModelIndex(),nNow,numberOfBonds_ - 1);
    numberOfBonds_ = nNow;
    endRemoveRows();
  }
  return pNewMol;
}

int ModelMolecularBondset::columnCount(const QModelIndex & /*parent*/) const
{
  return Column_Count;
}

int ModelMolecularBondset::rowCount(const QModelIndex & /*parent*/) const
{
  return numberOfBonds_;
}
