#include "SideBarDecorator.h"

#include "CodeEditor.h"

SideBarDecorator::SideBarDecorator(CodeEditor *editor)
    : QWidget(editor), theHost_(editor)
{
  Q_ASSERT(editor);
}

QSize SideBarDecorator::sizeHint() const
{
  Q_ASSERT(theHost_);
  return QSize(theHost_->SideBarWidth(), 0);
}

void SideBarDecorator::paintEvent(QPaintEvent *event)
{
  // Q_ASSERT(host_);
  theHost_->SideBarDecoratorPaintEvent(event);
}
