#include "ViewFilesystem.h"

ViewFilesystem::ViewFilesystem(QWidget* parent)
  : QSplitter(Qt::Vertical,parent)
  , browse_dir_(new BrowseFiles)
  , list_files_(new QListWidget)
{
  this->addWidget(list_files_);
  this->addWidget(browse_dir_);
}


ViewFilesystem::~ViewFilesystem(){}
