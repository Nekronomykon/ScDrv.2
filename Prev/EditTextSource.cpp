#include "EditTextSource.h"

#include <QFileInfo>

EditTextSource::EditTextSource(QWidget *parent)
    : EditCode(parent), file_dump_(tr("./SqD-XXXXXX.sq-drv"))
{
  file_dump_.setAutoRemove(true);
  this->dump();
}

EditTextSource::~EditTextSource()
{
  file_dump_.close(); // it is insisted...
}

bool EditTextSource::dump()
{
  if (!file_dump_.open())
    return false;
  file_dump_.resize(0L);
  this->save(&file_dump_);
  file_dump_.close();
  return true;
}

QString EditTextSource::getDumpPath() const
{
  return QFileInfo(file_dump_.fileName()).canonicalFilePath();
}
