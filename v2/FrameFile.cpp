#include "FrameFile.h"

#include <QWidget>

FrameFile::FrameFile(QWidget *parent)
: QTabWidget(parent)
, elements_(new TableElements(this))
{
  this->addTab(elements_, QString("Elements"));
}

void FrameFile::updateTabs()
{}