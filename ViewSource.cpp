#include "ViewSource.h"


ViewSource::ViewSource(QWidget* parent)
: QWidget(parent)
{
  this->setupUi(this);
  this->selectTextFormats_->addItem(QString(":: unrecognized format ::"));
}

EditTextSource* ViewSource::getTextSource() const
{
  return this->editTextSource_;
}
