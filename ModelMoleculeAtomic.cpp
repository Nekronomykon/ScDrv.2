#include "ModelMoleculeAtomic.h"

ModelMoleculeAtomic::ModelMoleculeAtomic(vtkMolecule *pMol)
    : QAbstractTableModel(), ptr_mol_(pMol)
{
}

vtkMolecule *ModelMoleculeAtomic::resetMolecule(vtkMolecule *pNewMol)
{
  if (pNewMol != ptr_mol_)
    std::swap(pNewMol, ptr_mol_);
  // this->resetInternalData();
  return pNewMol;
}

int ModelMoleculeAtomic::columnCount(const QModelIndex & /*parent*/) const
{
  return Column_Count;
}

int ModelMoleculeAtomic::rowCount(const QModelIndex & /*parent*/) const
{
  return (!ptr_mol_) ? 0 : (int)ptr_mol_->GetNumberOfAtoms();
}

QVariant ModelMoleculeAtomic::data(const QModelIndex &mi, int role) const
{
  QVariant res;

  if (role == Qt::DisplayRole)
    {
      assert(ptr_mol_);
      vtkAtom atom = ptr_mol_->GetAtom(mi.row());
      switch(mi.column())
      {
      case(ColumnElement): {res.setValue(atom.GetAtomicNumber()); break; }
        case(ColumnX):   { res.setValue((atom.GetPosition())[0]); break; }
        case(ColumnY):   { res.setValue((atom.GetPosition())[1]); break; }
        case(ColumnZ):   { res.setValue((atom.GetPosition())[2]); break; }
        default: break;
      }
    }

  return res;
}

QVariant ModelMoleculeAtomic::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Vertical || role != Qt::DisplayRole)
    return QAbstractTableModel::headerData(section, orientation, role); // ???
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
