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

