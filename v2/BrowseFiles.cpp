#include "BrowseFiles.h"

#include "ModelFiles.h"

#include <QItemSelectionModel>

#include <QModelIndex>
#include <QDir>

BrowseFiles::BrowseFiles(QWidget *parent)
    : _Base(parent)
{
  QModelIndex idx = this->GetViewModel()->setRootPath(QDir::rootPath());
  // this->setRootIndex(idx);

  this->clearSelection();
  this->setSelectionMode(QAbstractItemView::SingleSelection);
}
