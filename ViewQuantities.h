#ifndef View_Quantities_h__
#define View_Quantities_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>

#include "ui_ViewQuantities.h"

class ViewQuantities
    : public QWidget,
      private Ui_ViewQuantities
{
    Q_OBJECT
public:
    explicit ViewQuantities(QWidget* /*parent*/ = nullptr);
};

#endif // !View_Quantities_h__