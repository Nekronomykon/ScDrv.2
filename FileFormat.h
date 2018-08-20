#ifndef FileFormat_h
#define FileFormat_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QString>
#include <QWidget>

#include "ImplFileName.h"

template<class T>
class FileFormatContext;

template<class T>
// static inline
static inline bool operator <(const FileFormatContext<T> & f0, const FileFormatContext<T> &f1);

template<class T>
// static inline
static inline bool operator ==(const FileFormatContext<T> & f0, const FileFormatContext<T> &f1);

template<class T>
// static inline
static inline bool operator !=(const FileFormatContext<T> & f0, const FileFormatContext<T> &f1);


template<class T>
class FileFormatContext
{
  typedef typename T::TypeFileName TypeFileName;
  typedef bool (T::*BuildOperation)(void);
  typedef bool (T::*ExportOperation)(const TypeFileName&) const;

public:
  explicit FileFormatContext(TypeFileName name = TypeFileName()
    , BuildOperation opBuild = nullptr
    , ExportOperation opExport = nullptr)
    : name_format_(name)
    , build_operation_(opBuild)
    , export_operation_(opExport)
  {}

  const TypeFileName& nameFormat() const;

  bool isValid() const { return !FileNameRoot::isItEmpty(name_format_); }
  bool hasBuild()  const { return bool(build_operation_ != nullptr); }
  bool hasExport() const { return bool(build_operation_ != nullptr); }
  bool isCompatible(const TypeFileName& text) { return text.startsWith(name_format_); }
  const TypeFileName& FormatName() const { return name_format_; }

  operator TypeFileName () const { return name_format_; }
  bool operator !() const { return !this->isValid(); }

  // applying callbacks:
  bool buildFrom(T& obj, const TypeFileName& name) const;

  bool exportTo(T& obj, const TypeFileName& name) const
  {
    return (this->hasExport()) ?
      obj.*export_operation_(name) : false;
  }

  friend bool operator < <>(const FileFormatContext<T> & f0
    , const FileFormatContext<T> &f1);
  friend bool operator == <>(const FileFormatContext<T> & f0
    , const FileFormatContext<T> &f1);
  friend bool operator != <>(const FileFormatContext<T> & f0
    , const FileFormatContext<T> &f1);

private:
  TypeFileName name_format_;
  BuildOperation build_operation_;
  ExportOperation export_operation_;
};

template<class T>
class SetupDefaultFileContext
{
  typedef FileFormatContext<T> FileContext;
public:
  explicit SetupDefaultFileContext(const QString& sid)
    : context_current_(T::SetupFileInputContext(sid))
  {  }

  ~SetupDefaultFileContext() {
    T::ClearFileInputContext();
  }

  operator FileContext () const { return context_current_; }

private:
  FileContext context_current_;
};

#endif // !FileFormat_h
