#include "ViewFilesystem.h"

#include "ModelTextFiles.h"

#include <QModelIndex>
#include <QDir>

ViewFilesystem::ViewFilesystem(QWidget* parent)
  : QTreeView(parent)
  , model_txt_(new ModelTextFiles())
{
  
  QModelIndex idx = model_txt_->setRootPath(QDir::rootPath());
  this->setModel(model_txt_);
  //const QModelIndex rootIndex = model_txt_->index(QDir::cleanPath(""));
  //if (rootIndex.isValid())
  this->setRootIndex(idx);

  this->setAnimated(false);
  this->setSortingEnabled(true);
  // this->setCol
}


ViewFilesystem::~ViewFilesystem()
{
}
