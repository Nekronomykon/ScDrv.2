#include "TraitsAcquireAtoms.h"

using namespace std;

const double TraitsBase::AngstromInBohr = 0.52917721067;

string TraitsBase::ScrollEmptyStrings(BaseInput& in)
{
  string str_line;

  do
  {
    if (!getline(in, str_line))
      break;
    rtrim(str_line);
  } while (str_line.empty());

  return ltrim_copy(str_line);
}

size_t TraitsBase::MeasureStringGroup(BaseInput& in)
{
  string str_line = ScrollEmptyStrings(in);

  if (str_line.empty())
    return 0; // error, 'in' is not Ok...

  size_t nRes = 0;
  do
  {
    ++nRes;
    if (!getline(in, str_line))
      break;
    rtrim(str_line);
  } while (!str_line.empty());

  rtrim(str_line);

  if (!str_line.empty())
    ++nRes;

  return nRes;
}

bool TraitsBase::ScrollDownTo(BaseInput & in, const char * key_ptr)
{
  string key(key_ptr);
  if (key.empty())
    return false;

  string one_line;
  if (!std::getline(in, one_line))
    return false;
  do
  {
    rtrim(one_line);
    if (one_line.empty())
      continue;
    if (!one_line.compare(key))
      return true;
  } while (std::getline(in, one_line));

  return false;
}

vtkIdType TraitsBase::ElementSymbolToNumber(const char * symbol)
{
  if (!symbol || !*symbol)
    return 0L;
  vtkIdType number(id_Q);
  int k0 = std::toupper(*symbol);
  int k1 = !symbol[1] ? 0 : std::tolower(symbol[1]);
  switch (k0)
  {
  case('A'):
  {
    if (k1 == 'c') number = idAc;
    else if (k1 == 'g') number = idAg;
    else if (k1 == 'l') number = idAl;
    else if (k1 == 'm') number = idAm;
    else if (k1 == 'r') number = idAr;
    else if (k1 == 's') number = idAs;
    else if (k1 == 't') number = idAt;
    else if (k1 == 'u') number = idAu;
    break;
  }
  case('B'):
  {
    if (k1 == 'a') number = idBa;
    else if (k1 == 'e') number = idBe;
    else if (k1 == 'h') number = idBh;
    else if (k1 == 'i') number = idBi;
    else if (k1 == 'k') number = idBk;
    else if (k1 == 'r') number = idBr;
    else number = id_B;
    break;
  }
  case('C'):
  {
    if (k1 == 'a') number = idCa;
    else if (k1 == 'd') number = idCd;
    else if (k1 == 'e') number = idCe;
    else if (k1 == 'f') number = idCf;
    else if (k1 == 'l') number = idCl;
    else if (k1 == 'm') number = idCm;
    else if (k1 == 'n') number = idCn;
    else if (k1 == 'o') number = idCo;
    else if (k1 == 'r') number = idCr;
    else if (k1 == 's') number = idCs;
    else if (k1 == 'u') number = idCu;
    else number = id_C;
    break;
  }
  case('D'):
  {
    if (k1 == 'b') number = idDb;
    else if (k1 == 's') number = idDs;
    else if (k1 == 'y') number = idDy;
    break;
  }
  case('E'):
  {
    if (k1 == 'r') number = idEr;
    else if (k1 == 's') number = idEs;
    else if (k1 == 'u') number = idEu;
    break;
  }
  case('F'):
  {
    if (k1 == 'e') number = idFe;
    else if (k1 == 'l') number = idFl;
    else if (k1 == 'l') number = idFm;
    else number = id_F;
    break;
  }
  case('G'):
  {
    if (k1 == 'a') number = idGa;
    else if (k1 == 'd') number = idGd;
    else if (k1 == 'e') number = idGe;
    break;
  }
  case('H'):
  {
    if (k1 == 'e') number = idHe;
    else if (k1 == 'f') number = idHf;
    else if (k1 == 'g') number = idHg;
    else if (k1 == 'o') number = idHo;
    else if (k1 == 's') number = idHs;
    else number = id_H;
    break;
  }
  case('I'):
  {
    if (k1 == 'n') number = idIn;
    else if (k1 == 'r') number = idIr;
    else number = id_I;
    break;
  }
  // case('J'):
  case('K'):
  {
    if (k1 == 'r') number = idKr;
    else number = id_K;
    break;
  }
  case('L'):
  {
    if (k1 == 'a') number = idLa;
    else if (k1 == 'i') number = idLi;
    else if (k1 == 'r') number = idLr;
    else if (k1 == 'u') number = idLu;
    else if (k1 == 'v') number = idLv;
    break;
  }
  case('M'):
  {
    if (k1 == 'c') number = idMc;
    else if (k1 == 'd') number = idMd;
    else if (k1 == 'g') number = idMg;
    else if (k1 == 'o') number = idMo;
    else if (k1 == 'n') number = idMn;
    else if (k1 == 't') number = idMt;
    break;
  }
  case('N'):
  {
    if (k1 == 'a') number = idNa;
    else if (k1 == 'b') number = idNb;
    else if (k1 == 'd') number = idNd;
    else if (k1 == 'e') number = idNe;
    else if (k1 == 'h') number = idNh;
    else if (k1 == 'i') number = idNi;
    else if (k1 == 'o') number = idNo;
    else if (k1 == 'p') number = idNp;
    else number = id_N;
    break;
  }
  case('O'):
  {
    if (k1 == 'g') number = idOg;
    else if (k1 == 's') number = idOs;
    else number = id_O;
    break;
  }

  case('P'):
  {
    if (k1 == 'a') number = idPa;
    else if (k1 == 'b') number = idPb;
    else if (k1 == 'd') number = idPd;
    else if (k1 == 'm') number = idPm;
    else if (k1 == 'o') number = idPo;
    else if (k1 == 'r') number = idPr;
    else if (k1 == 't') number = idPt;
    else if (k1 == 'u') number = idPu;
    else number = id_P;
    break;
  }
  // case('Q'):
  case('R'):
  {
    if (k1 == 'a') number = idRa;
    else if (k1 == 'b') number = idRb;
    else if (k1 == 'e') number = idRe;
    else if (k1 == 'h') number = idRh;
    else if (k1 == 'f') number = idRf;
    else if (k1 == 'g') number = idRg;
    else if (k1 == 'n') number = idRn;
    else if (k1 == 'u') number = idRu;
    break;
  }
  case('S'):
  {
    if (k1 == 'b') number = idSb;
    else if (k1 == 'c') number = idSc;
    else if (k1 == 'e') number = idSe;
    else if (k1 == 'g') number = idSg;
    else if (k1 == 'i') number = idSi;
    else if (k1 == 'm') number = idSm;
    else if (k1 == 'n') number = idSn;
    else if (k1 == 'r') number = idSr;
    else number = id_S;
    break;
  }
  case('T'):
  {
    if (k1 == 'a') number = idTa;
    else if (k1 == 'b') number = idTb;
    else if (k1 == 'c') number = idTc;
    else if (k1 == 'e') number = idTe;
    else if (k1 == 'h') number = idTh;
    else if (k1 == 'i') number = idTi;
    else if (k1 == 'l') number = idTl;
    else if (k1 == 'm') number = idTm;
    else if (k1 == 's') number = idTs;
    break;
  }
  case('U'): {    number = id_U;    break;  }
  case('V'): {    number = id_V;    break;  }
  case('W'): {    number = id_W;    break;  }
  case('X'):
  {
    if (k1 == 'e') number = idXe;
    break;
  }
  case('Y'):
  {
    if (k1 == 'b') number = idYb;
    else number = id_Y;
    break;
  }
  case('Z'):
  {
    if (k1 == 'r') number = idZr;
    break;
  }
  default: break;
  }
  return number;
}
