#ifndef __Traits_AcquireAtoms_h__
#define __Traits_AcquireAtoms_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkMolecule.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <istream>
#include <sstream>
#include <string>

#include <cassert>

#include <algorithm> 
#include <cctype>
#include <locale>
// #include <charconv> // STD C++17

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
    return !std::isspace(ch);
  }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
    return !std::isspace(ch);
  }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
  rtrim(s);
  return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
  trim(s);
  return s;
}
/*********************************************************************************
  Traits specs:
**********************************************************************************/

struct TraitsBase
{
  typedef std::basic_istream<char, std::char_traits<char>> BaseInput;

  enum
  {
    id_Q = 0, 
    id_H = 1, idHe = 2, idLi = 3, idBe = 4, id_B = 5, id_C = 6, id_N = 7, id_O = 8, id_F = 9, idNe = 10,
    idNa = 11, idMg = 12, idAl = 13, idSi = 14, id_P = 15, id_S = 16, idCl = 17, idAr = 18,
    id_K = 19, idCa = 20, idSc = 21, idTi = 22, id_V = 23, idCr = 24, idMn = 25,
    idFe = 26, idCo = 27, idNi = 28, idCu = 29, idZn = 30, 
    idGa = 31, idGe = 32, idAs = 33, idSe = 34, idBr = 35, idKr = 36,
    idRb = 37, idSr = 38, id_Y = 39, idZr = 40, idNb = 41, idMo = 42, idTc = 43,
    idRu = 44, idRh = 45, idPd = 46, idAg = 47, idCd = 48,
    idIn = 49, idSn = 50, idSb = 51, idTe = 52, id_I = 53, idXe = 54, idCs = 55, idBa = 56, 
    idLa = 57, idCe = 58, idPr = 59, idNd = 60, idPm = 61, idSm = 62, idEu = 63, 
    idGd = 64, idTb = 65, idDy = 66, idHo = 67, idEr = 68, idTm = 69, idYb = 70, idLu = 71,
    idHf = 72, idTa = 73, id_W = 74, idRe = 75, idOs = 76, idIr = 77, idPt = 78, idAu = 79, idHg = 80,
    idTl = 81, idPb = 82, idBi = 83, idPo = 84, idAt = 85, idRn = 86, idFr = 87, idRa = 88,
    idAc = 89, idTh = 90, idPa = 91, id_U = 92, idNp = 93, idPu = 94, idAm = 95,
    idCm = 96, idBk = 97, idCf = 98, idEs = 99, idFm = 100, idMd = 101, idNo = 102, idLr = 103,
    idRf = 104, idDb = 105, idSg = 106, idBh = 107, idHs = 108, idMt = 109, idDs = 110, idRg = 111, idCn = 112,
    idNh = 113, idFl = 114, idMc = 115, idLv = 116, idTs = 117, idOg = 118,
    idUnknownYet = 255
  };

  static const double AngstromInBohr;

  static std::string ScrollEmptyStrings(BaseInput &/*in*/);
  static size_t MeasureStringGroup(BaseInput& /*in*/);
  static bool ScrollDownTo(BaseInput& /*in*/, const char* /*key*/);
  static std::string ScrollDownToPrefix(BaseInput& /*in*/, const char* /*key*/, size_t /*skip*/ = 0);

  static vtkIdType ElementSymbolToNumber(const char* symbol);
};

template<class T>
class TraitsEmpty
  : public TraitsBase
{};

/*********************************************************************************
  XMol XYZ format:
  (CHAR)SYMBOL X Y Z
**********************************************************************************/

template <class T> class TraitsSymbolicXYZ : public TraitsBase
{
public:
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    std::string str_line;

    assert(mol);
    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line))
        return -(++i);
      rtrim(str_line);
      if (str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);

      std::string atomType;
      float x, y, z;
      if (!(ssinp >> atomType >> x >> y >> z))
        return -(++i);
      int idType = ElementSymbolToNumber(atomType.c_str());
      mol->AppendAtom(idType, x, y, z);
      // mol->LabelAtom(i, atomType);
    }
    return 0;
  }
};

/*********************************************************************************
  MOPAC XYZ part format:
  NUM# SYMBOL X Y Z
**********************************************************************************/

template <class T> class TraitsNSymbolicXYZ : public TraitsBase
{
public:
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    // vtkNew<vtkPeriodicTable> ptrTable;
    std::string str_line;

    assert(mol);
    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line) || str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);

      size_t numThisAtom;
      std::string atomType;
      float x, y, z;
      if (!(ssinp >> numThisAtom >> atomType >> x >> y >> z))
        return -(++i);
      int idType = ElementSymbolToNumber(atomType.c_str());
      mol->AppendAtom(idType, x, y, z);
      // mol->LabelAtom(i, atomType);
    }
    return 0;
  }
};

/*********************************************************************************
  MOPAC +1 padded XYZ part format:
  NUM# SYMBOL X pad Y pad Z pad
**********************************************************************************/

template <class T>  class TraitsSymXYZPadded : public TraitsBase
{
public:
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    // vtkNew<vtkPeriodicTable> ptrTable;
    std::string str_line;
    std::string pad;

    assert(mol);
    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line) || str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);

      std::string atomType;
      std::string pad;
      float x, y, z;
      if (!(ssinp >> atomType >> x >> pad >> y >> pad >> z))
        return -(++i);
      mol->AppendAtom(ElementSymbolToNumber(atomType.c_str()), x, y, z);
      // mol->LabelAtom(i, atomType);
    }
    return 0;
  }
};

/*********************************************************************************
  CUBE XYZ format:
  (UNSIGNED INT)ATOM_NUM X Y Z
**********************************************************************************/

template <class T> class TraitsNumericXYZ : public TraitsBase
{
public:
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    std::string str_line;

    assert(mol);
    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line) || str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);

      unsigned short int atomType;
      float x, y, z;
      if (!(ssinp >> atomType >> x >> y >> z))
        return -(++i);
      mol->AppendAtom(atomType, x, y, z);
    }
    return 0;
  }
};

/*********************************************************************************
  GAMESS XYZ format:
  (CHAR)LABEL[10] (REAL)ATOM_NUM X Y Z
**********************************************************************************/
template <class T> class TraitsLabelNumberXYZ : public TraitsBase
{
public:
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    std::string str_line;

    assert(mol);
    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line) || str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);

      std::string label;
      float atomType;
      float x, y, z;
      if (!(ssinp >> label >> atomType >> x >> y >> z))
        return -(++i);
      mol->AppendAtom((unsigned short int)atomType, x, y, z);
      // mol->LabelAtom(i, label);
    }
    return 0;
  }
};

template <class T>
struct TraitsCentreWFN : TraitsBase
{
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(mol);

    std::string str_line;

    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line) || str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);
      std::string label;
      std::string skip;
      char c_skip;

      unsigned short int atomType;
      float x, y, z;
      if (!(ssinp >> label >> skip // <number> -> n_skip?
        >> skip                // "(CENTRE"
        >> skip                // "<number>)"
        >> x >> y >> z >> skip // "CHARGE"
        >> c_skip              // '='
        >> atomType))
        return -(++i);

      mol->AppendAtom(atomType
      , x // * AngstromInBohr,
      , y // * AngstromInBohr,
      , z // * AngstromInBohr
        );
      // mol->LabelAtom(i, label);
    }
    return 0;
  }
};

#endif // !__Traits_AcquireAtoms_h__
