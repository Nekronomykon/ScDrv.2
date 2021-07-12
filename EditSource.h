#ifndef EditSource_h__
#define EditSource_h__

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>
#include <QString>
#include <QTemporaryFile>

#include "EditCode.h"

class EditSource : public EditCode
{
  Q_OBJECT
public:
  EditSource(QWidget* parent = nullptr);

  // save the current content to a temporary file and return its path
  QString dumpTemporary();

  template <typename Parser>
  bool parseCurrentContent(Parser* parser);

private:
  static constexpr const char* name_template = "ScD-XXXXXX-src.sqdrv";

  QPointer<QTemporaryFile> source_tmp_;
};

#endif //! EditSource_h__
