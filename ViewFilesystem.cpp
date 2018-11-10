#include "ViewFilesystem.h"

#include <QFileInfo>

ViewFilesystem::ViewFilesystem(QWidget* parent)
  : QSplitter(Qt::Vertical,parent)
  , browse_dir_(new BrowseFilesystem)
  , list_files_(new BrowseFiles)
{
  this->addWidget(browse_dir_);
  this->addWidget(list_files_);

  connect(browse_dir_, &BrowseFilesystem::clicked
    , this, &ViewFilesystem::listDirectoryIndex);
  // browse_dir_->setRootIndex(browse_dir_->sele)
}

void ViewFilesystem::listDirectoryIndex(const QModelIndex& idx)
{
  auto *pMList = list_files_->GetViewModel();
  auto *pMTree = browse_dir_->GetViewModel();
  QString allname = pMTree->filePath(idx);
  QFileInfo fi = pMTree->fileInfo(idx);
  QString dir = fi.isDir() ? fi.canonicalFilePath() : fi.canonicalPath();
  list_files_->setRootIndex(pMList->index(dir));
  // list_files_->setItemSelected(pMList->index(fi.canonicalFilePath()));
}