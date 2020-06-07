#include "SideBarDecorator.h"

#include "EditCode.h"

SideBarDecorator::SideBarDecorator(EditCode *pEdit)
    : QWidget(pEdit), ptrHost_(pEdit)
{
  Q_ASSERT(pEdit);
}

QSize SideBarDecorator::sizeHint() const
{
  Q_ASSERT(ptrHost_);
  return QSize(ptrHost_->SideBarWidth(), 0);
}

void SideBarDecorator::paintEvent(QPaintEvent *event)
{
  // Q_ASSERT(host_);
  ptrHost_->SideBarDecoratorPaintEvent(event);
}
