#ifndef Molecular_AtomicModel_h
#define Molecular_AtomicModel_h

#include <QAbstractTableModel>
#include <QVariant>

class ModelMoleculeAtomic
    : public QAbstractTableModel
{
  Q_OBJECT
public:
  ModelMoleculeAtomic();

  int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
  int    rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
  QVariant data(const QModelIndex &, int) const override;

private:
  enum {
      ColumnID = 0
    , ColumnElement = 1
    , ColumnType    = 2
    , ColumnLabel   = 3
    , ColumnX       = 4
    , ColumnY       = 5
    , ColumnZ       = 6
    , Column_Count
  };
};

#endif // Molecular_AtomicModel_h
