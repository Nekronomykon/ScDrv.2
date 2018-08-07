#include "ViewMoleculeAtomic.h"

#include "ModelMoleculeAtomic.h"
#include <QAbstractTableModel>

ViewMoleculeAtomic::ViewMoleculeAtomic(QWidget* parent)
  : QTableView(parent)
{
  ModelMoleculeAtomic* pModel = new ModelMoleculeAtomic();
  this->setModel(pModel);
  this->setSelectionBehavior(QAbstractItemView::SelectRows);
}

ViewMoleculeAtomic::~ViewMoleculeAtomic(){}
