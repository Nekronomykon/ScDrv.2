#ifndef __Impl_FileName_h__
#define __Impl_FileName_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <string>

#include <vtkStdString.h>

#include <QString>
#include <QByteArray>

struct FileNameRoot
{
  template<class Str>
  inline static bool isItEmpty(const Str& s) { return s.empty(); }
  template<class Str>
  inline static const char* getPtrFrom(const Str& s) { return s.c_str(); }

  // for QString
  inline static bool isItEmpty(const QString& s) { return s.isEmpty(); }
  inline static const char* getPtrFrom(const QString& s)
  {
    static QByteArray buffer;
    buffer = s.toLatin1();
    return buffer.data();
  }
};

template <class T
  , class TName = std::string>
class ImplFileName
  : public FileNameRoot
{
public:
  typedef TName TypeFileName;

private:
  TypeFileName nameFile_;

protected:

public:
  const TypeFileName &path() const { return nameFile_; }
  TypeFileName &      path()       { return nameFile_; }
  TypeFileName     getPath() const { return nameFile_; }

  bool hasPath() const  { return !isItEmpty(nameFile_);  }

  TypeFileName resetPath(TypeFileName nameNew = TypeFileName())
  {
    nameNew.swap(nameFile_);
    T* pT = static_cast<T*>(this);
    pT->InterpretFileName();
    return nameNew;
  }

  const char *getPathPtr() const
  {
    return isItEmpty(nameFile_) ? nullptr : getPtrFrom(nameFile_);
  }

  void InterpretFileName(){}
};

#endif //!__Impl_FileName_h__
