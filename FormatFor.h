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
  typedef bool (Host::*Operation)(void);
  Operation operation_ = nullptr;

public:
  bool operator!() const { return bool(operation_ == nullptr); }

  const QString& name() const { return name_; }
  bool hasName() const { return !name_.isEmpty(); }
  const QString& extension() const { return extension_; }
  bool hasFileExtension() const { return !extension_.isEmpty(); }
  bool hasExtension(const QString& x) const { return !x.compare(extension_); }

  bool hasAction() const { return bool((Operation) nullptr != operation_); }

  bool checkInfo(const QFileInfo& info) const
  {
    return bool(!extension_.compare(info.suffix()));
  }
  bool applyFor(Host& host)
  {
    assert(operation_);
    return (!operation_) ? true :
      (host.*operation_)();
  }
};

#endif // !Format_For__h_
