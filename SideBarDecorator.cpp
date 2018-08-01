#include "SideBarDecorator.h"

#include "CodeEditor.h"

SideBarDecorator::SideBarDecorator(CodeEditor *editor)
    : QWidget(editor), host_(editor)
{
  Q_ASSERT(editor);
}

QSize SideBarDecorator::sizeHint() const
{
  Q_ASSERT(host_);
  return QSize(host_->SideBarWidth(), 0);
}

void SideBarDecorator::paintEvent(QPaintEvent *event)
{
  // Q_ASSERT(host_);
  host_->SideBarDecoratorPaintEvent(event);
}
