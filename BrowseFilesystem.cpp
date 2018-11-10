#include "BrowseFilesystem.h"

#include <QAbstractItemView>
#include <QModelIndex>
#include <QDir>

BrowseFilesystem::BrowseFilesystem(QWidget *parent)
  : _Base(parent)
{
}

void BrowseFilesystem::SetupModel(ModelFilesystem * pM)
{
  pM->setFilter(QDir::Drives | QDir::Dirs | QDir::AllDirs | QDir::Readable);
  // pM->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);
  QModelIndex idx = this->GetViewModel()->setRootPath(QDir::rootPath());
  // this->setRootIndex(idx);
  this->clearSelection();
  this->setSelectionMode(QAbstractItemView::SingleSelection);

  this->setAnimated(false);
  this->setSortingEnabled(true);
}
