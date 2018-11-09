#include "ModelFiles.h"

ModelFiles::ModelFiles()
  : QFileSystemModel()
{}


ModelFiles::~ModelFiles()
{}


int ModelFiles::columnCount(const QModelIndex&)const
{
  return 1; // Only full-path file name
}
