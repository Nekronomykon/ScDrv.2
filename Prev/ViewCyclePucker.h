#ifndef __View_CyclePucker_h
#define __View_CyclePucker_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>

#include "ui_ViewCyclePucker.h"

class ViewCyclePucker
    : public QWidget
    , private Ui_ViewCyclePucker
{
  Q_OBJECT
public:
  explicit ViewCyclePucker(QWidget* /*parent*/ = nullptr);
  ~ViewCyclePucker() override = default;
};

#endif // !__View_CyclePucker_h