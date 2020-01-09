#include "ModelFiles.h"

ModelFiles::ModelFiles()
  : QFileSystemModel()
{}


ModelFiles::~ModelFiles()
{}


int ModelFiles::columnCount(const QModelIndex&)const
{
  return 1; // only file name
}
