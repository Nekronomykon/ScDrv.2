#include "ModelMoleculeAtomic.h"

ModelMoleculeAtomic::ModelMoleculeAtomic()
: QAbstractTableModel()
{}

int ModelMoleculeAtomic::columnCount(const QModelIndex & /*parent*/) const
{
  return Column_Count;
}

int ModelMoleculeAtomic::rowCount(const QModelIndex & /*parent*/) const
{
  return 217; // just a stub here
}

QVariant ModelMoleculeAtomic::data(const QModelIndex &mi, int role) const
{
  return (role == Qt::DisplayRole) ? QVariant((float)1.25 + (mi.row() + mi.column()) / 3.5).toDouble() : QVariant();
}

QVariant ModelMoleculeAtomic::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Vertical || role != Qt::DisplayRole)
    return QAbstractTableModel::headerData(section, orientation, role);
  QVariant res;
  switch (section)
  {
  case (ColumnID):
  {
    res.setValue(tr("ID"));
    break;
  }
  case (ColumnElement):
  {
    res.setValue(tr("Element"));
    break;
  }
  case (ColumnType):
  {
    res.setValue(tr("Atom type"));
    break;
  }
  case (ColumnLabel):
  {
    res.setValue(tr("User label"));
    break;
  }
  case (ColumnX):
  {
    res.setValue(tr("X"));
    break;
  }
  case (ColumnY):
  {
    res.setValue(tr("Y"));
    break;
  }
  case (ColumnZ):
  {
    res.setValue(tr("Z"));
    break;
  }
  default:
  {
    res.setValue(tr("Comment"));
    break;
  }
  }
  return res;
}

bool ModelMoleculeAtomic::setData(const QModelIndex &index, const QVariant &value, int role)
{
  return false;
  // stub... WUT?
}

 Qt::ItemFlags ModelMoleculeAtomic::flags(const QModelIndex &index) const
 {
         if (!index.isValid())
          return Qt::ItemIsEnabled;

      return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;

 }