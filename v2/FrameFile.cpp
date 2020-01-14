#include "FrameFile.h"

#include <QWidget>

FrameFile::FrameFile(QWidget *parent)
: QTabWidget(parent)
// , elements_(new TableElements(this))
, source_(new EditTextSource(this))
{
  // this->addTab(elements_, QString("Elements"));
  this->addTab(source_, QString("Source[*]") );
}

void FrameFile::updateTabs()
{
  int iEdit = this->indexOf(source_);
  if(iEdit >= 0)
  {
    bool bModified = this->isSourceModified();
  }
}