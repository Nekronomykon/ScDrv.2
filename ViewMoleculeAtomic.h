#ifndef ViewMolecule_Atomic_h
#define ViewMolecule_Atomic_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>
#include <QWidget>

#include "DelegateElements.h"
#include "ModelMoleculeAtomic.h"

#include <QTableView>
#include "ImplModelView.h"

class ViewMoleculeAtomic
    : public ImplModelView<ViewMoleculeAtomic,QTableView,ModelMoleculeAtomic>
{
  typedef ImplModelView<ViewMoleculeAtomic,QTableView,ModelMoleculeAtomic> _Base;
  Q_OBJECT
public:
  ViewMoleculeAtomic (QWidget* /*parent*/ = nullptr);
  ~ViewMoleculeAtomic () override;

private:
  QPointer<DelegateElements> delegate_Mendeleev_;
};

#endif // ViewMolecule_Atomic_h
