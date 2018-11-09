#include "BrowseFiles.h"

#include "ModelFiles.h"

#include <QItemSelectionModel>

#include <QModelIndex>
#include <QDir>

BrowseFiles::BrowseFiles(QWidget *parent)
    : QTreeView(parent), model_txt_(new ModelFiles())
{
  QItemSelectionModel *pSel;

  this->setModel(model_txt_);
  QModelIndex idx = model_txt_->setRootPath(QDir::rootPath());
  this->setRootIndex(idx);

  this->clearSelection();
  this->setSelectionMode(QAbstractItemView::SingleSelection);

  this->setAnimated(false);
  this->setSortingEnabled(true);
}

BrowseFiles::~BrowseFiles() {}
