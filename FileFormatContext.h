#ifndef __FileInput_Context_h__
#define __FileInput_Context_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QString>

#include "ImplFileName.h"

template<class T>
class FileFormatContext
{
  typedef typename T::FileNameType FileName;
  typedef bool (T::*BuildOperation)(void);
  typedef bool (T::*ExportOperation)(const FileName&);

public:
  FileFormatContext(FileName ext = FileName()
    , BuildOperation opBuild = nullptr
    , ExportOperation opExport = nullptr)
    : format_ext_(ext)
    , build_operation_(opBuild)
    , export_operation_(opExport)
  {}

  bool isValid() const { return FileNameRoot::isItEmpty(format_ext_); }
  bool hasBuild()  const { return bool(build_operation_ != nullptr); }
  bool hasExport() const { return bool(build_operation_ != nullptr); }

  operator FileName () const { return format_ext_; }
  bool operator !() const { return !this->isValid(); }
  bool buildFrom(T& obj, const FileName& name) const
  {
    if (obj.readSource(name))
      return (this->hasBuild()) ? obj.*build_operation_() : true;
    else
      return false;
  }

  bool exportTo(T& obj, const FileName& name) const
  {
    return (this->hasExport()) ?
      obj.*export_operation_(name) : false;
  }

private:
  FileName format_ext_;
  BuildOperation build_operation_;
  ExportOperation export_operation_;
};

template<class T>
class FileInputContextSetup
{
public:
  explicit FileInputContextSetup(const QString& sid) {
    T::SetupFileInputContext(sid);
  }

  ~FileInputContextSetup() {
    T::ClearFileInputContext();
  }

};

#endif // !__FileInput_Context_h__
