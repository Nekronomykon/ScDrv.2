#include "BrowseFilesystem.h"

#include <QAbstractItemView>
#include <QModelIndex>
#include <QDir>

BrowseFilesystem::BrowseFilesystem(QWidget *parent)
  : _Base(parent)
{}

void BrowseFilesystem::SetupModel(ModelFilesystem * pM)
{
  _Base::SetupModel(pM);

  QModelIndex idx = pM->setRootPath(QDir::rootPath());
  // this->setRootIndex(idx);
  
  this->clearSelection();
  this->setSelectionMode(QAbstractItemView::SingleSelection);

  this->setAnimated(false);
  this->setSortingEnabled(true);
}
