#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QTableView>

#include <vtkPeriodicTable.h>
#include "ModelElements.h"
#include "ImplModelView.h"

class TableElements
    : public ImplModelView<TableElements, QTableView, ModelElements>
{
  typedef ImplModelView<TableElements, QTableView, ModelElements> _Base;

  Q_OBJECT

public:
  explicit TableElements(QWidget* /*parent*/ = nullptr);

};

#endif // PERIODICTABLE_H
