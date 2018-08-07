#ifndef MODELELEMENTS_H
#define MODELELEMENTS_H

#include <vtkNew.h>
#include <vtkPeriodicTable.h>

#include <QAbstractTableModel>

class ModelElements
    : public QAbstractTableModel
{
  Q_OBJECT

  enum {NumberOfElements = 118
        , NumberOfPeriods = 8
        , NumberOfGroups = 18
        , NumberOfSpecialSeq = 2
       };
public:
  ModelElements();

  int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
  {return NumberOfGroups;}
  int    rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
  {return NumberOfPeriods + NumberOfSpecialSeq;}
  QVariant data(const QModelIndex & /*index*/, int /*role*/) const override;


private:
  vtkNew<vtkPeriodicTable> elements_;

};

#endif // MODELELEMENTS_H
