#include "ViewMoleculeAtomic.h"

#include "ModelMoleculeAtomic.h"
#include <QAbstractTableModel>
#include "DelegateElements.h"

ViewMoleculeAtomic::ViewMoleculeAtomic(QWidget* parent)
  : QTableView(parent)
  , delegate_Mendeleev_(new DelegateElements())
{
  ModelMoleculeAtomic* pModel = new ModelMoleculeAtomic();
  this->setModel(pModel);
  this->setSelectionBehavior(QAbstractItemView::SelectRows);
}

ViewMoleculeAtomic::~ViewMoleculeAtomic(){}