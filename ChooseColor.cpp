#include "ChooseColor.h"

#include <vtkNamedColors.h>

QString ChooseColor::name_color_bg(tr("alice_blue"));

ChooseColor::ChooseColor(QWidget *parent)
    : QComboBox(parent)
{
  // this->addItem(QString("-- user --")); // placeholder
  this->addItems(ColorNames());
}

QStringList ChooseColor::ColorNames()
{
  static QStringList allNames;

  if (allNames.isEmpty())
  {
    vtkNew<vtkStringArray> col_names;
    vtkNew<vtkNamedColors> named_colors;
    named_colors->GetColorNames(col_names);
    size_t nNames = col_names->GetSize();
    for (size_t j = 0; j < nNames; ++j)
    {
      vtkStdString a_name(col_names->GetValue(j));
      if (a_name.empty())
        continue;
      QString sName(tr(a_name.c_str()));
      if (!sName.isEmpty())
        allNames << sName;
    }
  }

  return allNames;
}
