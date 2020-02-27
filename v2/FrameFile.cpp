#include "FrameFile.h"

#include <QWidget>

FrameFile::FrameFile(QWidget *parent)
: QTabWidget(parent)
, source_(new EditTextSource(this))
{
    this->setTabPosition(QTabWidget::South);
    // this->setTabsClosable(true);
    this->setTabBarAutoHide(true);
    this->setTabShape(QTabWidget::Rounded);

  // this->addTab(elements_, QString("Elements"));
  this->addTab(source_, QString("Source") );
}

void FrameFile::updateTabs()
{
  int iEdit = this->indexOf(source_);
  if(iEdit >= 0)
  {
    bool bModified = this->isSourceModified();
  }
}

bool FrameFile::interpretSource(const QString& pathcontext)
{
  return true;
}