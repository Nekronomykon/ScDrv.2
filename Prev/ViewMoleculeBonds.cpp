#include "ViewMoleculeBonds.h"

ViewMoleculeBonds::ViewMoleculeBonds(QWidget*parent)
: _Base(parent)
{
  this->setSelectionBehavior(QAbstractItemView::SelectRows);
}

ViewMoleculeBonds::~ViewMoleculeBonds(){}