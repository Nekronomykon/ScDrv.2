#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#include <QTableView>

#include <vtkPeriodicTable.h>

class PeriodicTable
    : public QTableView
{
  Q_OBJECT

public:
  explicit PeriodicTable(QWidget* /*parent*/ = nullptr);

};

#endif // PERIODICTABLE_H
