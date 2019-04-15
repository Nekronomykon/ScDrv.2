#include "ComboBoxColors.h"

vtkStdString ComboBoxColors::bgcolor_default("antique_white");
vtkNew<vtkNamedColors> ComboBoxColors::named_colors;

ComboBoxColors::ComboBoxColors(QWidget *parent)
    : QComboBox(parent)
{
  this->addItems(GetBackgroundColorNames());

  QString name(bgcolor_default.c_str());

  int nSel = this->findText(name);
  if (nSel < 0)
    name = tr("white"); // ??
  this->setCurrentText(name);
}

QStringList ComboBoxColors::GetBackgroundColorNames()
{
  static QStringList allNames;
  
  if (allNames.isEmpty())
  {
    vtkNew<vtkStringArray> col_names;

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

