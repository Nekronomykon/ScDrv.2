#include "TableElements.h"

TableElements::TableElements(QWidget *parent)
  : _Base(parent)
{
  this->setSelectionMode(QAbstractItemView::SingleSelection);
  this->setShowGrid(false);
  
  //QFont fontSrc("Courier", 10);
  //fontSrc.setStyleHint(QFont::Monospace);
  //fontSrc.setBold(true);
  //this->setFont(fontSrc);

  QFontMetrics fm = this->fontMetrics();

  int w1 = fm.width(QLatin1Char('9')) * 4;
  int h1 = fm.height(); // * 3 / 2;

  Model* pM = this->GetViewModel();

  /// ???
  for (int j = 0; j <= pM->columnCount(); 
    this->setColumnWidth(j++, w1));

  for (int j = 0; j <= pM->rowCount();
    this->setRowHeight(j++, h1));

  int kwidth = (pM->columnCount() + 1)* w1;
  int kheight = (pM->rowCount() + 3) * h1;
  this->setGeometry(0, 0, kwidth, kheight);
}

