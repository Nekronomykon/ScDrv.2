#include "FileFormat.h"

template<class T>
static inline bool operator <(const FileFormatContext<T> & f0, const FileFormatContext<T> &f1)
{
  return (f0.name_format_ < f1.name_format_);
}

template<class T>
static inline bool operator ==(const FileFormatContext<T> & f0, const FileFormatContext<T> &f1)
{
  return (f0.name_format_ == f1.name_format_);
}

template<class T>
static inline bool operator !=(const FileFormatContext<T> & f0, const FileFormatContext<T> &f1)
{
  return (f0.name_format_ != f1.name_format_);
}


template<class T>
const typename  FileFormatContext<T>::TypeFileName &
FileFormatContext<T>::nameFormat() const { return name_format_; }

template<class T>
bool FileFormatContext<T>::buildFrom(T &obj
                                     , const typename FileFormatContext<T>::TypeFileName &name) const
{
  QWidget *pView = obj.currentWidget();
  obj.doClearAll();
  if (!obj.readTextSource(name))
    return false;

  obj.ResetFileName(name);
  obj.getEditSource()->setReadOnly(false);
  bool bRes = true;
  if (this->hasBuild())
    {
      bool bBuilt = (obj.*build_operation_)();
      if (bBuilt) obj.showStructureViews();
      obj.getEditSource()->setReadOnly(bBuilt);
    }
  obj.setCurrentWidget(pView);
  return bRes;
}
