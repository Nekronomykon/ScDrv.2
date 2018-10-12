#include "BrowseFiles.h"

#include "ModelTextFiles.h"

#include <QItemSelectionModel>

#include <QModelIndex>
#include <QDir>

BrowseFiles::BrowseFiles(QWidget *parent)
    : QTreeView(parent), model_txt_(new ModelTextFiles())
{
  QItemSelectionModel *pSel;

  QModelIndex idx = model_txt_->setRootPath(QDir::rootPath());
  //QModelIndex idx = model_txt_->setRootPath(QDir::currentPath());
  this->setModel(model_txt_);
  //const QModelIndex rootIndex = model_txt_->index(QDir::cleanPath(""));
  //if (rootIndex.isValid())
  this->setRootIndex(idx);
  // this->setRootIndex( model_txt_->setRootPath(QDir::currentPath()) );
  // this->selectionMode

  this->clearSelection();
  this->setSelectionMode(QAbstractItemView::SingleSelection);

  this->setAnimated(false);
  this->setSortingEnabled(true);
  // this->setCol
}

BrowseFiles::~BrowseFiles() {}
