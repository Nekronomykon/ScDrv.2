#ifndef __Edit_TextSource_h__
#define __Edit_TextSource_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include "EditCode.h"

#include <QTemporaryFile>
#include <QWidget>

/*
EditTextSource --- editor class; owner and proxy for the temporarily persistent text file.
*/

class EditTextSource
    : public EditCode
{
  Q_OBJECT
public:
  explicit EditTextSource(QWidget* /*parent */ = Q_NULLPTR);
  ~EditTextSource() override;

  //
  bool dump();
  QString getDumpPath() const;


private:
  QTemporaryFile file_dump_;

};

#endif // !__Edit_TextSource_h__
