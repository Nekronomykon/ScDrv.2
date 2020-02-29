#ifndef ComboBox_NamedColors_h
#define ComboBox_NamedColors_h

#include <QComboBox>

#include <vtkNew.h>
#include <vtkStdString.h>
#include <vtkNamedColors.h>

class ComboBoxColors
    : public QComboBox
{
  Q_OBJECT
public:
  ComboBoxColors(QWidget * /*parent*/ = nullptr);

private:
  static QStringList ColorNames();
};

#endif // !ComboBox_NamedColors_h
