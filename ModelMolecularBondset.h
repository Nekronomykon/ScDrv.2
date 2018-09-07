#ifndef MODELMOLECULARBONDSET_H
#define MODELMOLECULARBONDSET_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkMolecule.h>
#include <vtkType.h>

#include <QModelIndex>
#include <QVariant>

#include <QAbstractTableModel>

class ModelMolecularBondset
    : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit ModelMolecularBondset(vtkMolecule * /*pMol*/ = nullptr);
  ~ModelMolecularBondset() override;

  vtkMolecule *getMolecule() const { return ptr_mol_; }
  vtkMolecule *resetMolecule(vtkMolecule * /*pNewMol*/ = nullptr);

  enum
  {
    ColumnID = 0,
    ColumnFrom = 1,
    ColumnTo = 2,
    ColumnType = 3,
    ColumnLength = 4,
    Column_Count
  };

  int columnCount(const QModelIndex & /*parent*/ = QModelIndex()) const override;

  int rowCount(const QModelIndex & /*parent*/ = QModelIndex()) const override;

  QVariant data(const QModelIndex &, int) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  vtkMolecule *ptr_mol_; // ??? MolecularStructure* ptr_structure_;
  vtkIdType numberOfBonds_;

};

#endif // MODELMOLECULARBONDSET_H
