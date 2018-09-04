#include "SymmetryComboBox.h"

SymmetryComboBox::SymmetryComboBox(QWidget *parent)
  : QComboBox(parent)
{
  QStringList all_sym(tr("C1"));
  all_sym << QString("Ci")   << QString("Cs")   << QString("C2")
          << QString("C_n") << QString("C_nv") << QString("C_nh") << QString("S_n")
          << QString("D_n") << QString("D_nd") << QString("D_nh")
          << QString("T")   << QString("Td")
          << QString("O")   << QString("Od")   << QString("Oh")
          << QString("I")   << QString("Ih")
          << QString("K")   << QString("Kh"); // two spheric...
  this->addItems(all_sym);
  this->setCurrentIndex(0);

}
