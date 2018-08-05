#include "ModelTextFiles.h"

ModelTextFiles::ModelTextFiles()
  : QFileSystemModel()
{}


ModelTextFiles::~ModelTextFiles()
{}


int ModelTextFiles::columnCount(const QModelIndex&)const
{
  return 1; // Only full-path file name
}
