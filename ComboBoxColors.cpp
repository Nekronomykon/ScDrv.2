#include "ComboBoxColors.h"

#include <QLatin1String>

#include <vtkStringArray.h>

vtkNew<vtkNamedColors> ComboBoxColors::namedColors;

ComboBoxColors::ComboBoxColors(QWidget* parent)
  : QComboBox(parent)
{
  this->loadColorNames();
}

void ComboBoxColors::loadColorNames(void)
{
  vtkNew<vtkStringArray> names;
  namedColors->GetColorNames(names);
  size_t nNames = names->GetSize();
  for (size_t j = 0; j < nNames; ++j)
  {
    vtkStdString a_name(names->GetValue(j));
    QString str_name( tr(a_name.c_str() ) );
    this->addItem(str_name);
  }
}