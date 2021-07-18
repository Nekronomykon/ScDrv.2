#include "EditSource.h"

#include <QFileInfo>

inline /* static */ QString EditSource::nameTemplate()
{
  return tr(name_template);
}

EditSource::EditSource(QWidget* parent)
  : EditCode(parent)
  , source_tmp_()
{
}

QString EditSource::dumpTemporary()
{
  QString path_res;
  // save the current content to a temporary file
  if (!source_tmp_)
    source_tmp_ = new QTemporaryFile(nameTemplate());

  if (source_tmp_->open())
    this->save(source_tmp_);

  if (source_tmp_->flush())
    path_res = source_tmp_->fileName();

  source_tmp_->close();
  return path_res;
}

template <class Parser>
bool EditSource::parseCurrentContentWith(Parser* parser)
{
  QString path_res;
  // save the current content to a temporary file
  if (!source_tmp_)
    source_tmp_ = new QTemporaryFile(nameTemplate());

  if (source_tmp_->open()) {
    this->save(source_tmp_);

  } else {
    return false; // react on the error of no open
  }

  path_res = source_tmp_->fileName();
  if (source_tmp_->flush()) {
    ; // flush Ok
  } else {
    ; // react on the error of no flush
  }
  source_tmp_->close(); // mandatory?

  bool bSysOk = path_res.isEmpty();
  if (bSysOk) {
    QByteArray bytes = path_res.toLatin1();
    parser->SetFileName(bytes.data());
    parser->Update();
  } else {
    ; // react on the error of no name
  }
  return bSysOk;
}