#include "ModelMoleculeAtomic.h"

#include <QGuiApplication>
#include <QStringLiteral>

#include <vtkAtom.h>
#include "Elements.h"

#include <QPalette>

ModelMoleculeAtomic::ModelMoleculeAtomic(vtkMolecule *pMol)
    : QAbstractTableModel()
    , ptr_mol_(pMol)
    , numberOfAtoms_(!pMol ? 0 : pMol->GetNumberOfAtoms())
{}

ModelMoleculeAtomic::~ModelMoleculeAtomic(){}

vtkMolecule *ModelMoleculeAtomic::resetMolecule(vtkMolecule *pNewMol)
{
  if (pNewMol != ptr_mol_) // reassign if ptr changed
    std::swap(pNewMol, ptr_mol_);
    
  vtkIdType nNow = !ptr_mol_ ? 0 : ptr_mol_->GetNumberOfAtoms();
  if(nNow > numberOfAtoms_)
  {
    this->beginInsertRows(QModelIndex(),numberOfAtoms_,nNow - 1);
    numberOfAtoms_ = nNow;
    this->endInsertRows();
  }
  if(nNow < numberOfAtoms_)
  {
    this->beginRemoveRows(QModelIndex(),nNow,numberOfAtoms_ - 1);
    numberOfAtoms_ = nNow;
    this->endRemoveRows();
  }
  return pNewMol;
}

int ModelMoleculeAtomic::columnCount(const QModelIndex & /*parent*/) const
{
  return Column_Count;
}

int ModelMoleculeAtomic::rowCount(const QModelIndex & /*parent*/) const
{
  return numberOfAtoms_;
}

QVariant ModelMoleculeAtomic::data(const QModelIndex &mi, int role) const
{
  if (!mi.isValid())
    return QVariant();
  if (!ptr_mol_ || mi.row() >= ptr_mol_->GetNumberOfAtoms())
    return QVariant();
  if (role == Qt::DisplayRole)
  {
    QVariant res;
    vtkNew<PeriodicElements> elem;
    vtkAtom atom = ptr_mol_->GetAtom(mi.row());
    switch (mi.column())
    {
    case (ColumnElement):
    {
      res.setValue(QString(elem->GetSymbol( atom.GetAtomicNumber() ) ) );
      break;
    }
    case (ColumnNumber):
    {
      res.setValue(atom.GetAtomicNumber());
      break;
    }
    case (ColumnX):
    {
      res.setValue((atom.GetPosition())[0]);
      break;
    }
    case (ColumnY):
    {
      res.setValue((atom.GetPosition())[1]);
      break;
    }
    case (ColumnZ):
    {
      res.setValue((atom.GetPosition())[2]);
      break;
    }
    default:
      break;
    }

    return res;
  }
  else if (role == Qt::BackgroundRole)
  {
    return (mi.row() + 1) % 2 ?
    qApp->palette().base() : qApp->palette().alternateBase();
  }
  else
    return QVariant();
}

QVariant ModelMoleculeAtomic::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();
  if (orientation == Qt::Vertical)
    return QStringLiteral("[%1]").arg(section);
  QVariant res;
  switch (section)
  {
  case (ColumnID):
  {
    res.setValue(tr("Atom ID"));
    break;
  }
  case (ColumnElement):
  {
    res.setValue(tr("Element"));
    break;
  }
  case (ColumnNumber):
  {
    res.setValue(tr("Number"));
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
    // res.setValue(tr("Comment"));
    break;
  }
  }
  return res;
}

bool ModelMoleculeAtomic::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role == Qt::EditRole)
  {
  }
  return true;
}

Qt::ItemFlags ModelMoleculeAtomic::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
