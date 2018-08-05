#ifndef __SideBar_Decorator_h__
#define __SideBar_Decorator_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QSize>
#include <QPaintEvent>
#include <QWidget>

class CodeEditor;

//![codeeditordefinition]
//![extraarea]

class SideBarDecorator
    : public QWidget
{
public:
  explicit SideBarDecorator(CodeEditor *editor);
  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  CodeEditor *theHost_;
};

//![extraarea]

#endif // !__SideBar_Decorator_h__
