#include "ModelMolecularBondset.h"

#include <vtkBond.h>

#include <QGuiApplication>
#include <QStringLiteral>

#include <QPalette>

ModelMolecularBondset::ModelMolecularBondset(vtkMolecule *pMol)
    : QAbstractTableModel(), ptr_mol_(pMol), numberOfBonds_(pMol ? pMol->GetNumberOfBonds() : 0)
{
}

ModelMolecularBondset::~ModelMolecularBondset() {}

vtkMolecule *ModelMolecularBondset::resetMolecule(vtkMolecule *pNewMol)
{
  if (pNewMol != ptr_mol_) // reassign if ptr changed
    std::swap(pNewMol, ptr_mol_);
  vtkIdType nNow = !ptr_mol_ ? 0 : ptr_mol_->GetNumberOfBonds();
  if (nNow > numberOfBonds_)
  {
    beginInsertRows(QModelIndex(), numberOfBonds_, nNow - 1);
    numberOfBonds_ = nNow;
    endInsertRows();
  }
  if (nNow < numberOfBonds_)
  {
    beginRemoveRows(QModelIndex(), nNow, numberOfBonds_ - 1);
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

QVariant ModelMolecularBondset::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();
  if (orientation == Qt::Vertical)
    return QStringLiteral("Bond %1").arg(section + 1);
  QVariant res;
  switch (section)
  {
  case (ColumnFrom):
  {
    res.setValue(tr("From atom"));
    break;
  }
  case (ColumnTo):
  {
    res.setValue(tr("To atom"));
    break;
  }
  case (ColumnLength):
  {
    res.setValue(tr("Bond length"));
    break;
  }
  defaut:
    break;
  }
  return res;
}

bool ModelMolecularBondset::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role == Qt::EditRole)
  {
  }
  return true;
}

Qt::ItemFlags ModelMolecularBondset::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant ModelMolecularBondset::data(const QModelIndex &mi, int role) const
{
  if (!mi.isValid())
    return QVariant();
  if (!ptr_mol_ || mi.row() >= ptr_mol_->GetNumberOfAtoms())
    return QVariant();
  if (role == Qt::DisplayRole)
  {
    QVariant res;
    assert(ptr_mol_);
    vtkBond atom = ptr_mol_->GetBond(mi.row());
    switch (mi.column())
    {
    default:
      break;
    }
    return res;
  }
  else if (role == Qt::BackgroundRole)
  {
    return (mi.row() + 1) % 2 ? qApp->palette().base() : qApp->palette().alternateBase();
  }
  else
    return QVariant();
}
