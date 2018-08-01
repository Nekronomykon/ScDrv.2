#ifndef __Cursor_Helper_h__
#define __Cursor_Helper_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QCursor>

class ResetCursor
{
public:
  explicit ResetCursor(const QCursor&);
  ~ResetCursor();

private:
  ResetCursor();
  ResetCursor(const ResetCursor&);
};

#endif // !__Cursor_Helper_h__
