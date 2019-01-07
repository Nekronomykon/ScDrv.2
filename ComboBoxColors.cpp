#include "ComboBoxColors.h"

#include "FrameFile.h"

ComboBoxColors::ComboBoxColors(QWidget *parent)
  : QComboBox(parent)
{
  this->addItems(FrameFile::GetBackgroundColorNames());
  vtkStdString s_one(FrameFile::ViewMolecule::GetDefaultBackgroundColorName());
  QString name(s_one.c_str());

  int nSel = this->findText(name);
  if (nSel < 0)
    name = tr("white");
  this->setCurrentText(name);
}
