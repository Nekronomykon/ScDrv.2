#ifndef Format_For__h_
#define Format_For__h_

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QString>
#include <QFileInfo>

template <class Host>
struct FileFormatFor
{
  QString name_;
  QString extension_;
  typedef void (Host::*Operation)(void);
  Operation operation_ = nullptr;

  bool checkInfo(const QFileInfo &info) const { return bool(!extension_.compare(info.suffix())); }
  void applyFor(Host &host)
  {
    assert(operation_);
    if (operation_)
      (host.*operation_)();
  }
};

#endif // !Format_For__h_
