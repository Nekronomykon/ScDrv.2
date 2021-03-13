#include "ModelFilesystem.h"

#include <QModelIndex>


int ModelFilesystem::columnCount(const QModelIndex&)const
{
  return 1; // Only full-path file name
}
