#ifndef View_TextAtomic_H__
#define View_TextAtomic_H__

#include "ui_ViewTextAtomic.h"

class QWidget;

class ViewTextAtomic
: public QWidget
, private Ui_ViewTextAtomic
{
private:
    /* data */
public:
    ViewTextAtomic(QWidget* /*parent*/ = nullptr);
    ~ViewTextAtomic() override = default;
};

#endif // ! View_TextAtomic_H__

