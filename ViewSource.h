#ifndef __View_Source_h
#define __View_Source_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include "EditTextSource.h"

#include <QWidget>
#include <QVBoxLayout>

#include "ui_ViewSource.h"

class ViewSource
: public QWidget
, private Ui_ViewSource
{
  Q_OBJECT
   public: 
   explicit ViewSource(QWidget* /*parent*/ = nullptr);
   ~ViewSource() override = default;
private:
};

#endif //! __View_Source_h
