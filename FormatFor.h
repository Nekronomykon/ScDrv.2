#ifndef Format_For__h_
#define Format_For__h_

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QFileInfo>
#include <QString>

template <class Host>
struct FileFormatFor
{
  QString name_;
  QString extension_;
  typedef void (Host::*Operation)(void);
  Operation operation_ = nullptr;

public:
  bool operator!() const { return bool(operation_ == nullptr); }

  const QString& name() const { return name_; }
  bool hasName() const { return !name_.isEmpty(); }
  const QString& extension() const { return extension_; }
  bool hasFileExtension() const { return !extension_.isEmpty(); }

  bool hasAction() const { return bool((Operation) nullptr != operation_); }

  bool checkInfo(const QFileInfo& info) const
  {
    return bool(!extension_.compare(info.suffix()));
  }
  void applyFor(Host& host)
  {
    assert(operation_);
    if (operation_)
      (host.*operation_)();
  }
};

#endif // !Format_For__h_
