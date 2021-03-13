#include "ViewMoleculeAtomic.h"

#include "ModelMoleculeAtomic.h"
#include <QAbstractTableModel>

#include "DelegateElementTable.h"
#include "DelegateElementSpin.h"

ViewMoleculeAtomic::ViewMoleculeAtomic(QWidget *parent)
    : _Base(parent)
    , delegate_Mendeleev_(new DelegateElementTable())
    , delegate_ScrollElements_(new DelegateElementSpin())
{
  this->setSelectionBehavior(QAbstractItemView::SelectRows);
  this->setItemDelegateForColumn(ModelMoleculeAtomic::ColumnElement, delegate_Mendeleev_);
  this->setItemDelegateForColumn(ModelMoleculeAtomic::ColumnNumber, delegate_ScrollElements_);
}

ViewMoleculeAtomic::~ViewMoleculeAtomic() {}
