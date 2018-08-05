#ifndef __Edit_TextSource_h__
#define __Edit_TextSource_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include "CodeEditor.h"

#include <QWidget>

class EditTextSource
    : public CodeEditor
{
  Q_OBJECT
public:
  EditTextSource(QWidget* /*parent */ = Q_NULLPTR);
};

#endif // !__Edit_TextSource_h__
