#include "ViewFilesystem.h"

ViewFilesystem::ViewFilesystem(QWidget* parent)
  : QSplitter(Qt::Vertical,parent)
  , list_files_(new QListWidget)
  , browse_dir_(new BrowseFiles)
{
  this->addWidget(list_files_);
  this->addWidget(browse_dir_);
}


ViewFilesystem::~ViewFilesystem(){}
