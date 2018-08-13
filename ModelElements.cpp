#include "ModelElements.h"

const unsigned short ModelElements::NobleGases[]
= { 2,  10,  18,  36,  54,  86, 118, NumberOfElements + 1 };
//   He   Ne   Ar   Kr   Xe   Rn   Og    <finish>

const unsigned short ModelElements::InGroup[] =
{ 1, /*  H                                                     He */ 18
, 1,  2 /* Be                              B */, 13, 14, 15, 16, 17, 18
, 1,  2 /* Mg                             Al */, 13, 14, 15, 16, 17, 18
, 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18
, 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18
, 1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
           ,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18
, 1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
           ,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18

};

ModelElements::ModelElements()
{}

QVariant ModelElements::data(const QModelIndex & index, int /*role*/) const
{
  QVariant res;
  // cast index.row() and index.column() into the idElement in the Table;
  return res;
}
