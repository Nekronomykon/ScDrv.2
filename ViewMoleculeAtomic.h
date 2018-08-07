#ifndef ViewMolecule_Atomic_h
#define ViewMolecule_Atomic_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>
#include <QWidget>

#include "DelegateElements.h"

#include <QTableView>

class ViewMoleculeAtomic
    : public QTableView
{
  Q_OBJECT
public:
  ViewMoleculeAtomic (QWidget* /*parent*/ = nullptr);
  ~ViewMoleculeAtomic () override;

private:
  QPointer<DelegateElements> delegate_Mendeleev_;
};

#endif // ViewMolecule_Atomic_h
