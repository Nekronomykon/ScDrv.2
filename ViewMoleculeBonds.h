#ifndef ViewMolecule_Bonds__h
#define ViewMolecule_Bonds__h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include "ImplModelView.h"
#include "ModelMoleculeBondset.h"

class ViewMoleculeBonds
: public ImplModelView<ViewMoleculeBonds,QTableView,ModelMolecularBondset>
{
  typedef ImplModelView<ViewMoleculeBonds,QTableView,ModelMolecularBondset> _Base;
  Q_OBJECT
  public:
  explicit ViewMoleculeBonds(QWidget* /*parent*/ = nullptr);
  ~ViewMoleculeBonds() override;
};

#endif // !ViewMolecule_Bonds__h