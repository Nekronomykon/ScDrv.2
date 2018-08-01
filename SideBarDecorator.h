#ifndef __SideBar_Decorator_h__
#define __SideBar_Decorator_h__

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
  CodeEditor *host_;
};

//![extraarea]

#endif // !__SideBar_Decorator_h__
