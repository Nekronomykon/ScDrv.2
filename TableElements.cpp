#include "TableElements.h"

#include "ModelElements.h"

TableElements::TableElements(QWidget *parent)
  : QTableView(parent)
{
  ModelElements* pModel = new ModelElements();
  this->setModel(pModel);
}

