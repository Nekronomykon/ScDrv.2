#include "ViewCyclePucker.h"

#include <QTreeWidgetItem>

ViewCyclePucker::ViewCyclePucker(QWidget* parent):QWidget(parent)
{
  this->setupUi(this);

  // init systems
  selectSystem_->addItem(tr("Cremer-Pople"));

  // init pucker items:
  cyclePucker_->setColumnCount(2);
  QTreeWidgetItem* rootString = new QTreeWidgetItem;
  rootString->setText(0,"Cycle string");
  cyclePucker_->addTopLevelItem(rootString);
}