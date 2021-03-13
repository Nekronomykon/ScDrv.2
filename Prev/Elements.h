#ifndef Elements_h
#define Elements_h

#include <vtkType.h>
#include <vtkStdString.h>

class Elements
{
private:
  enum
  {
    id_Q = 0,
    id_H = 1,
    idHe = 2,
    idLi = 3,
    idBe = 4,
    id_B = 5,
    id_C = 6,
    id_N = 7,
    id_O = 8,
    id_F = 9,
    idNe = 10,
    idNa = 11,
    idMg = 12,
    idAl = 13,
    idSi = 14,
    id_P = 15,
    id_S = 16,
    idCl = 17,
    idAr = 18,
    id_K = 19,
    idCa = 20,
    idSc = 21,
    idTi = 22,
    id_V = 23,
    idCr = 24,
    idMn = 25,
    idFe = 26,
    idCo = 27,
    idNi = 28,
    idCu = 29,
    idZn = 30,
    idGa = 31,
    idGe = 32,
    idAs = 33,
    idSe = 34,
    idBr = 35,
    idKr = 36,
    idRb = 37,
    idSr = 38,
    id_Y = 39,
    idZr = 40,
    idNb = 41,
    idMo = 42,
    idTc = 43,
    idRu = 44,
    idRh = 45,
    idPd = 46,
    idAg = 47,
    idCd = 48,
    idIn = 49,
    idSn = 50,
    idSb = 51,
    idTe = 52,
    id_I = 53,
    idXe = 54,
    idCs = 55,
    idBa = 56,
    idLa = 57,
    idCe = 58,
    idPr = 59,
    idNd = 60,
    idPm = 61,
    idSm = 62,
    idEu = 63,
    idGd = 64,
    idTb = 65,
    idDy = 66,
    idHo = 67,
    idEr = 68,
    idTm = 69,
    idYb = 70,
    idLu = 71,
    idHf = 72,
    idTa = 73,
    id_W = 74,
    idRe = 75,
    idOs = 76,
    idIr = 77,
    idPt = 78,
    idAu = 79,
    idHg = 80,
    idTl = 81,
    idPb = 82,
    idBi = 83,
    idPo = 84,
    idAt = 85,
    idRn = 86,
    idFr = 87,
    idRa = 88,
    idAc = 89,
    idTh = 90,
    idPa = 91,
    id_U = 92,
    idNp = 93,
    idPu = 94,
    idAm = 95,
    idCm = 96,
    idBk = 97,
    idCf = 98,
    idEs = 99,
    idFm = 100,
    idMd = 101,
    idNo = 102,
    idLr = 103,
    idRf = 104,
    idDb = 105,
    idSg = 106,
    idBh = 107,
    idHs = 108,
    idMt = 109,
    idDs = 110,
    idRg = 111,
    idCn = 112,
    idNh = 113,
    idFl = 114,
    idMc = 115,
    idLv = 116,
    idTs = 117,
    idOg = 118,
    idNumberOfElements = 119,
    idUnknownYet = 255,
    idAtomNumberMask = 0x0fff
  };

  static const char *Symbol[idNumberOfElements];
  /* {  "Xx",  "H",  "He",
  "Li",  "Be",  "B",  "C",  "N",  "O",  "F",  "Ne",
  "Na",  "Mg",  "Al",  "Si",  "P",  "S",  "Cl",  "Ar",
  "K",  "Ca",  "Sc",  "Ti",  "V",  "Cr",  "Mn",  "Fe",  "Co",  "Ni",
  "Cu",  "Zn",  "Ga",  "Ge",  "As",  "Se",  "Br",  "Kr",
  "Rb",  "Sr",  "Y",  "Zr",  "Nb",  "Mo",  "Tc",  "Ru",  "Rh",  "Pd",
  "Ag",  "Cd",  "In",  "Sn",  "Sb",  "Te",  "I",  "Xe",
  "Cs",  "Ba",  "La",  "Ce",  "Pr",  "Nd",  "Pm",  "Sm",  "Eu",  "Gd",  "Tb",  "Dy",  "Ho",  "Er",  "Tm",  "Yb",  "Lu",
  "Hf",  "Ta",  "W",  "Re",  "Os",  "Ir",  "Pt",
  "Au",  "Hg",  "Tl",  "Pb",  "Bi",  "Po",  "At",  "Rn",
  "Fr",  "Ra",  "Ac",  "Th",  "Pa",  "U",  "Np",  "Pu",  "Am",  "Cm",  "Bk",  "Cf",  "Es",  "Fm",  "Md",  "No",  "Lr",
  "Rf",  "Db",  "Sg",  "Bh",  "Hs",  "Mt",  "Ds",
  "Rg",  "Cn",  "Nh",  "Fl",  "Mc",  "Lv",  "Ts",  "Og"
}*/;

static const char *Name[idNumberOfElements];


public:
  static vtkIdType NumberOfElements() { return idNumberOfElements; }
  static vtkIdType SymbolToNumber(const char *);
  static bool IsValidAtomNumber(vtkIdType idAtomType)
  {
    return ((idAtomType & idAtomNumberMask) < idUnknownYet);
  }

  static vtkStdString GetElementSymbol(vtkIdType);
};

#endif //!Elements_h
