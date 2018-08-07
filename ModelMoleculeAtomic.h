#ifndef Molecular_AtomicModel_h
#define Molecular_AtomicModel_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QAbstractTableModel>
#include <QVariant>

class ModelMoleculeAtomic
  : public QAbstractTableModel
{
  Q_OBJECT
public:
  ModelMoleculeAtomic();

  int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
  
  int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
  
  QVariant data(const QModelIndex &
    , int) const override;
  
  QVariant headerData(int section
    , Qt::Orientation orientation
    , int role = Qt::DisplayRole) const override;
    
    bool setData(const QModelIndex &index
    , const QVariant &value
    , int role = Qt::EditRole) override;

     Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  enum {
    ColumnID = 0
    , ColumnLabel = 1
    , ColumnElement = 2
    , ColumnType = 3
    , ColumnX = 4
    , ColumnY = 5
    , ColumnZ = 6
    , Column_Count
  };
};

#endif // Molecular_AtomicModel_h
