#include "ModelMoleculeAtomic.h"

ModelMoleculeAtomic::ModelMoleculeAtomic()
{}

int ModelMoleculeAtomic::columnCount(const QModelIndex & /*parent*/) const
{
  return (int)Column_Count;
}

int ModelMoleculeAtomic::rowCount(const QModelIndex & /*parent*/) const
{
  return 217; // just a stub here
}

QVariant ModelMoleculeAtomic::data(const QModelIndex &, int) const
{
  return QVariant();
}