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

  static QStringList GetBackgroundColorNames();

  vtkStdString GetBackgroundColorName() const;
  vtkStdString ResetBackgroundColorName(vtkStdString name_new);


private:
  static vtkNew<vtkNamedColors> named_colors;
  static vtkStdString bgcolor_default;
};

#endif // !ComboBox_NamedColors_h
