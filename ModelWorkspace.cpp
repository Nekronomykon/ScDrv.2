#include "ModelWorkspace.h"



ModelWorkspace::ModelWorkspace(){}


ModelWorkspace::~ModelWorkspace(){}


int ModelWorkspace::columnCount(const QModelIndex &) const
{
  return 2;
}