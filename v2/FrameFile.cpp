#include "FrameFile.h"

#include <QWidget>

FrameFile::FrameFile(QWidget *parent)
: QTabWidget(parent)
, source_(new EditTextSource(this))
, visual_(new ViewStructure(this))
, molecule_(Molecule::New())
{
    this->setTabPosition(QTabWidget::South);
    // this->setTabsClosable(true);
    this->setTabBarAutoHide(true);
    this->setTabShape(QTabWidget::Rounded);

  // this->addTab(elements_, QString("Elements"));
  source_->setReadOnly(true);
  this->addTab(source_, QString("Source") );

  this->addTab(visual_,QString("Structure"));
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