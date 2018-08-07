#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QTableView>

#include <vtkPeriodicTable.h>

class TableElements
    : public QTableView
{
  Q_OBJECT

public:
  explicit TableElements(QWidget* /*parent*/ = nullptr);

};

#endif // PERIODICTABLE_H
