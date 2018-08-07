#include "ModelElements.h"

ModelElements::ModelElements()
{}

QVariant ModelElements::data(const QModelIndex & index, int /*role*/) const
{
  QVariant res;
  // cast index.row() and index.column() into the idElement in the Table;
  return res;
}
