#ifndef MODELELEMENTS_H
#define MODELELEMENTS_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkNew.h>
#include <vtkPeriodicTable.h>

#include <QAbstractTableModel>

class ModelElements
  : public QAbstractTableModel
{
  Q_OBJECT

    enum {
    NumberOfElements = 135
    , NumberOfPeriods = 8
    , NumberOfGroups = 18
    , NumberOfSpecialSeq = 3 // Ln --- lantanides, Aq --- actinides, Sq --- superactinides
    , LengthSpecialSec = 15
  };

  static const unsigned short NobleGases[NumberOfPeriods];
  static const unsigned short InGroup[];
public:
  ModelElements();

  int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
  {
    return NumberOfGroups;
  }
  int    rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
  {
    return NumberOfPeriods + NumberOfSpecialSeq;
  }
  QVariant data(const QModelIndex & /*index*/, int /*role*/) const override;


private:
  vtkNew<vtkPeriodicTable> elements_;

};

#endif // MODELELEMENTS_H
