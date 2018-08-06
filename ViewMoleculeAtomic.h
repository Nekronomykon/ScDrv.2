#ifndef ViewMolecule_Atomic_h
#define ViewMolecule_Atomic_h

#include <QTableView>
#include <QWidget>

class ViewMoleculeAtomic
    : public QTableView
{
  Q_OBJECT
public:
  ViewMoleculeAtomic (QWidget* /*parent*/ = nullptr);
  ~ViewMoleculeAtomic () override;
};

#endif // ViewMolecule_Atomic_h
