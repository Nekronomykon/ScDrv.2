#include "ViewFilesystem.h"

#include <QDir>
#include <QFileInfo>

ViewFilesystem::ViewFilesystem(QWidget *parent)
    : QSplitter(Qt::Vertical, parent),
      modelFileSystem_(new QFileSystemModel),
      treeFileSystem_(new QTreeView(this)),
      listFiles_(new QListView(this))

{
    this->setOpaqueResize(false);

    modelFileSystem_->setOption(QFileSystemModel::DontUseCustomDirectoryIcons, true);
    modelFileSystem_->setRootPath(QDir::rootPath());

    listFiles_->setAlternatingRowColors(true);
    listFiles_->setModel(modelFileSystem_);
    this->addWidget(listFiles_);

    treeFileSystem_->setAlternatingRowColors(true);
    treeFileSystem_->setModel(modelFileSystem_);
    treeFileSystem_->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->addWidget(treeFileSystem_);

    this->listFilesAt(modelFileSystem_->index(QDir::currentPath()));

    connect(treeFileSystem_, &QTreeView::clicked, this, &ViewFilesystem::listFilesAt);
    connect(listFiles_, &QTreeView::doubleClicked, this, &ViewFilesystem::listFilesAt);
}

QFileInfo ViewFilesystem::fileInfo(const QModelIndex &idx)
{
    return modelFileSystem_->fileInfo(idx);
}

void ViewFilesystem::listFilesAt(const QModelIndex &idx)
{
    QFileInfo fi(modelFileSystem_->fileInfo(idx));
    QString set_root = fi.isDir() ? fi.canonicalFilePath() : fi.canonicalPath();
    QModelIndex idx_root = modelFileSystem_->index(set_root);
    listFiles_->setRootIndex(idx_root);
    treeFileSystem_->setCurrentIndex(idx_root);
    listFiles_->setCurrentIndex(idx);
}
