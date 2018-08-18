#include "ModelElements.h"

const unsigned short ModelElements::NobleGases[]
= { 2,  10,  18,  36,  54,  86, 118, NumberOfElements + 1 };
// He   Ne   Ar   Kr   Xe   Rn   Og    <finish>

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

const vtkIdType ModelElements::TableForm[] =
{// 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18
    1, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1, -1, -1, -1, -1, -1, -1,  2,
    3,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  5,  6,  7,  8,  9, 10,
   11, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 14, 15, 16, 17, 18,
   19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
   37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
   55, 56, -2, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
   87, 88, -3,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,
  119,120, -4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
   -1, -1, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, -1,
   -1, -1, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103, -1,
   //   -1, -1,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135, -1
};

const vtkIdType ModelElements::NumTable
= sizeof(ModelElements::TableForm) / sizeof(ModelElements::TableForm[0]);

ModelElements::ModelElements()
{}

QVariant ModelElements::data(const QModelIndex & index, int role) const
{
  QVariant res;
  // cast index.row() and index.column() into the idElement in the Table;
  if (role == Qt::DisplayRole)
  {
    vtkIdType ofs = index.row() * NumberOfGroups + index.column();
    if (ofs < NumTable)
    {
      vtkIdType idElem = TableForm[ofs];
      if (idElem >= 0)
      {
        res.setValue(tr(elements_->GetSymbol(idElem)));
      }
      else if (idElem == -2) res.setValue(tr("[L]"));
      else if (idElem == -3) res.setValue(tr("[A]"));
      else if (idElem == -4) res.setValue(tr("[S]"));
    }
  }
  return res;
}
