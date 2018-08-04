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
  const TypeFileName &FileName() const { return nameFile_; }
  TypeFileName &      FileName()       { return nameFile_; }
  TypeFileName     GetFileName() const { return nameFile_; }

  bool HasFileName() const
  {
    return !isItEmpty(nameFile_);
  }

  TypeFileName ResetFileName(TypeFileName nameNew = TypeFileName())
  {
    nameNew.swap(nameFile_);
    T* pT = static_cast<T*>(this);
    pT->InterpretFileName();
    return nameNew;
  }

  const char *GetFileNamePtr() const
  {
    const T *pT = static_cast<const T *>(this);
    return pT->HasFileName() ? getPtrFrom(nameFile_) : nullptr;
  }

  void InterpretFileName(){}
};

#endif //!__Impl_FileName_h__
