#ifndef ChooseColor_byName__h
#define ChooseColor_byName__h

#include <QString>
#include <QStringList>
#include <QComboBox>

#include <vtkNew.h>
#include <vtkStdString.h>
#include <vtkNamedColors.h>

class ChooseColor
    : public QComboBox
{
  Q_OBJECT
public:
  ChooseColor(QWidget * /*parent*/ = nullptr);

private:
  static QStringList ColorNames();
  static QString name_color_bg;
};

#endif // !ChooseColor_byName__h
