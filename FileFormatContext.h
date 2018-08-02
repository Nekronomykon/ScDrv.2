#ifndef __FileInput_Context_h__
#define __FileInput_Context_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QString>

#include "ImplFileName.h"

template<class T>
struct FileFormatContext
{
  typedef typename T::FileNameType FileName;
  typedef bool (T::*BuildOperation)(void);
  typedef bool (T::*ExportOperation)(const FileName&);

  bool hasBuild()  const { return bool(build_operation_ != nullptr);  }

  bool hasExport() const { return bool(build_operation_ != nullptr);  }

  bool buildFrom(T& obj, const FileName& name) const
  {
    if(!this->hasBuild())
      return false; // you would check it before

    return obj.readSource(name) ?
          obj.*build_operation_() : false;

  }

  bool exportTo(T& obj, const FileName& name) const
  {
    return (this->hasExport()) ?
          obj.*export_operation_(name) : false;
  }

  FileName annoteFormat(bool bExt = false) const
  {
    FileName res(format_name_);
    if (bExt) {
        res += " (*.";
        res += format_ext_;
        res += ");;";
      }
    return res;
  }

  FileName format_name_;
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
