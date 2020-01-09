#include "EditTextSource.h"

#include <QFileInfo>

EditTextSource::EditTextSource(QWidget* parent)
  : EditCode (parent)
  , file_dump_(tr("./SqD-XXXXXX.sq-drv"))
{
  file_dump_.setAutoRemove(true);
  file_dump_.open();
}

EditTextSource::~EditTextSource()
{
  file_dump_.close();
}

void EditTextSource::dump()
{
  this->save(&file_dump_);
  file_dump_.flush();
  file_dump_.seek(0L);
}

QString EditTextSource::getDumpPath() const
{
  return QFileInfo(file_dump_.fileName()).canonicalFilePath();
}
