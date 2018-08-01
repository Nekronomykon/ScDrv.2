#ifndef __FileInput_Context_h__
#define __FileInput_Context_h__

#include <QString>

#include "ImplFileName.h"

template<class T>
struct FileInputContext
{
  typedef typename T::FileNameType FileName;
  typedef bool(T::*BuildOperation)(void);

  bool hasBuild() const 
  { 
    return bool(build_operation_ != (BuildOperation)nullptr);
  }

  bool buildFrom(T& obj, const FileName& name) const
  {
    assert(build_operation_); // you should check it before
    if (!build_operation_)
      return false;

    return obj.readSourceFrom(name) ?
      obj.*build_operation_() : false;

  }

  FileName annoteFormat(bool bExt = false) const
  {
    FileName res(format_name_);
    if (bExt) {
      res += " (*.";
      res += format_ext_;
      res += ");;";
    }
    returm res;
  }

  FileName format_name_;
  FileName format_ext_;
  BuildOperation build_operation_;
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
