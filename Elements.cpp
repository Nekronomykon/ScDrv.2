#include "Elements.h"

#include <cctype>

const char *Elements::Symbol[] = {"Xx",
  "H",  "He",
  "Li",  "Be",  "B",  "C",  "N",  "O",  "F",  "Ne",
  "Na",  "Mg",  "Al",  "Si",  "P",  "S",  "Cl",  "Ar",
  "K",  "Ca",  "Sc",  "Ti",  "V",  "Cr",  "Mn",  "Fe",  "Co",  "Ni",
  "Cu",  "Zn",  "Ga",  "Ge",  "As",  "Se",  "Br",  "Kr",
  "Rb",  "Sr",  "Y",  "Zr",  "Nb",  "Mo",  "Tc",  "Ru",  "Rh",  "Pd",
  "Ag",  "Cd",  "In",  "Sn",  "Sb",  "Te",  "I",  "Xe",
  "Cs",
  "Ba",
  "La",
  "Ce",
  "Pr",
  "Nd",
  "Pm",
  "Sm",
  "Eu",
  "Gd",
  "Tb",
  "Dy",
  "Ho",
  "Er",
  "Tm",
  "Yb",
  "Lu",
  "Hf",
  "Ta",
  "W",
  "Re",
  "Os",
  "Ir",
  "Pt",
  "Au",
  "Hg",
  "Tl",
  "Pb",
  "Bi",
  "Po",
  "At",
  "Rn",
  "Fr",
  "Ra",
  "Ac",
  "Th",
  "Pa",
  "U",
  "Np",
  "Pu",
  "Am",
  "Cm",
  "Bk",
  "Cf",
  "Es",
  "Fm",
  "Md",
  "No",
  "Lr",
  "Rf",
  "Db",
  "Sg",
  "Bh",
  "Hs",
  "Mt",
  "Ds",
  "Rg",
  "Cn",
  "Nh",
  "Fl",
  "Mc",
  "Lv",
  "Ts",
  "Og"
};

const char *Elements::Name[119] = {
  "Dummy",
  "Hydrogen",
  "Helium",
  "Lithium",
  "Beryllium",
  "Boron",
  "Carbon",
  "Nitrogen",
  "Oxygen",
  "Fluorine",
  "Neon",
  "Sodium",
  "Magnesium",
  "Aluminium",
  "Silicon",
  "Phosphorus",
  "Sulfur",
  "Chlorine",
  "Argon",
  "Potassium",
  "Calcium",
  "Scandium",
  "Titanium",
  "Vanadium",
  "Chromium",
  "Manganese",
  "Iron",
  "Cobalt",
  "Nickel",
  "Copper",
  "Zinc",
  "Gallium",
  "Germanium",
  "Arsenic",
  "Selenium",
  "Bromine",
  "Krypton",
  "Rubidium",
  "Strontium",
  "Yttrium",
  "Zirconium",
  "Niobium",
  "Molybdenum",
  "Technetium",
  "Ruthenium",
  "Rhodium",
  "Palladium",
  "Silver",
  "Cadmium",
  "Indium",
  "Tin",
  "Antimony",
  "Tellurium",
  "Iodine",
  "Xenon",
  "Caesium",
  "Barium",
  "Lanthanum",
  "Cerium",
  "Praseodymium",
  "Neodymium",
  "Promethium",
  "Samarium",
  "Europium",
  "Gadolinium",
  "Terbium",
  "Dysprosium",
  "Holmium",
  "Erbium",
  "Thulium",
  "Ytterbium",
  "Lutetium",
  "Hafnium",
  "Tantalum",
  "Tungsten",
  "Rhenium",
  "Osmium",
  "Iridium",
  "Platinum",
  "Gold",
  "Mercury",
  "Thallium",
  "Lead",
  "Bismuth",
  "Polonium",
  "Astatine",
  "Radon",
  "Francium",
  "Radium",
  "Actinium",
  "Thorium",
  "Protactinium",
  "Uranium",
  "Neptunium",
  "Plutonium",
  "Americium",
  "Curium",
  "Berkelium",
  "Californium",
  "Einsteinium",
  "Fermium",
  "Mendelevium",
  "Nobelium",
  "Lawrencium",
  "Rutherfordium",
  "Dubnium",
  "Seaborgium",
  "Bohrium",
  "Hassium",
  "Meitnerium",
  "Darmstadtium",
  "Roentgenium",
  "Copernicium",
  "Nihonium",
  "Flerovium",
  "Moscovium",
  "Livermorium",
  "Tenessine",
  "Oganesson"
};


vtkIdType Elements::SymbolToNumber(const char *symbol)
{
  if (!symbol || !*symbol)
    return 0L;
  vtkIdType number(id_Q);
  int k0 = toupper(*symbol),
      k1 = !symbol[1] ? 0 : tolower(symbol[1]),
      k2 = ((k0 != 'U') || !k1 || !symbol[2]) ? 0 : tolower(symbol[2]); 
      // rare cases of the Uu? / Ub? / Ut? heavy elements
  switch (k0)
  {
  case ('A'):
  {
    if (k1 == 'c')
      number = idAc;
    else if (k1 == 'g')
      number = idAg;
    else if (k1 == 'l')
      number = idAl;
    else if (k1 == 'm')
      number = idAm;
    else if (k1 == 'r')
      number = idAr;
    else if (k1 == 's')
      number = idAs;
    else if (k1 == 't')
      number = idAt;
    else if (k1 == 'u')
      number = idAu;
    break;
  }
  case ('B'):
  {
    if (k1 == 'a')
      number = idBa;
    else if (k1 == 'e')
      number = idBe;
    else if (k1 == 'h')
      number = idBh;
    else if (k1 == 'i')
      number = idBi;
    else if (k1 == 'k')
      number = idBk;
    else if (k1 == 'r')
      number = idBr;
    else
      number = id_B;
    break;
  }
  case ('C'):
  {
    if (k1 == 'a')
      number = idCa;
    else if (k1 == 'd')
      number = idCd;
    else if (k1 == 'e')
      number = idCe;
    else if (k1 == 'f')
      number = idCf;
    else if (k1 == 'l')
      number = idCl;
    else if (k1 == 'm')
      number = idCm;
    else if (k1 == 'n')
      number = idCn;
    else if (k1 == 'o')
      number = idCo;
    else if (k1 == 'r')
      number = idCr;
    else if (k1 == 's')
      number = idCs;
    else if (k1 == 'u')
      number = idCu;
    else
      number = id_C;
    break;
  }
  case ('D'):
  {
    if (k1 == 'b')
      number = idDb;
    else if (k1 == 's')
      number = idDs;
    else if (k1 == 'y')
      number = idDy;
    break;
  }
  case ('E'):
  {
    if (k1 == 'r')
      number = idEr;
    else if (k1 == 's')
      number = idEs;
    else if (k1 == 'u')
      number = idEu;
    break;
  }
  case ('F'):
  {
    if (k1 == 'e')
      number = idFe;
    else if (k1 == 'l')
      number = idFl;
    else if (k1 == 'm')
      number = idFm;
    else
      number = id_F;
    break;
  }
  case ('G'):
  {
    if (k1 == 'a')
      number = idGa;
    else if (k1 == 'd')
      number = idGd;
    else if (k1 == 'e')
      number = idGe;
    break;
  }
  case ('H'):
  {
    if (k1 == 'e')
      number = idHe;
    else if (k1 == 'f')
      number = idHf;
    else if (k1 == 'g')
      number = idHg;
    else if (k1 == 'o')
      number = idHo;
    else if (k1 == 's')
      number = idHs;
    else
      number = id_H;
    break;
  }
  case ('I'):
  {
    if (k1 == 'n')
      number = idIn;
    else if (k1 == 'r')
      number = idIr;
    else
      number = id_I;
    break;
  }
  // case('J'):
  case ('K'):
  {
    if (k1 == 'r')
      number = idKr;
    else
      number = id_K;
    break;
  }
  case ('L'):
  {
    if (k1 == 'a')
      number = idLa;
    else if (k1 == 'i')
      number = idLi;
    else if (k1 == 'r')
      number = idLr;
    else if (k1 == 'u')
      number = idLu;
    else if (k1 == 'v')
      number = idLv;
    break;
  }
  case ('M'):
  {
    if (k1 == 'c')
      number = idMc;
    else if (k1 == 'd')
      number = idMd;
    else if (k1 == 'g')
      number = idMg;
    else if (k1 == 'o')
      number = idMo;
    else if (k1 == 'n')
      number = idMn;
    else if (k1 == 't')
      number = idMt;
    break;
  }
  case ('N'):
  {
    if (k1 == 'a')
      number = idNa;
    else if (k1 == 'b')
      number = idNb;
    else if (k1 == 'd')
      number = idNd;
    else if (k1 == 'e')
      number = idNe;
    else if (k1 == 'h')
      number = idNh;
    else if (k1 == 'i')
      number = idNi;
    else if (k1 == 'o')
      number = idNo;
    else if (k1 == 'p')
      number = idNp;
    else
      number = id_N;
    break;
  }
  case ('O'):
  {
    if (k1 == 'g')
      number = idOg;
    else if (k1 == 's')
      number = idOs;
    else
      number = id_O;
    break;
  }

  case ('P'):
  {
    if (k1 == 'a')
      number = idPa;
    else if (k1 == 'b')
      number = idPb;
    else if (k1 == 'd')
      number = idPd;
    else if (k1 == 'm')
      number = idPm;
    else if (k1 == 'o')
      number = idPo;
    else if (k1 == 'r')
      number = idPr;
    else if (k1 == 't')
      number = idPt;
    else if (k1 == 'u')
      number = idPu;
    else
      number = id_P;
    break;
  }
  // case('Q'):
  case ('R'):
  {
    if (k1 == 'a')
      number = idRa;
    else if (k1 == 'b')
      number = idRb;
    else if (k1 == 'e')
      number = idRe;
    else if (k1 == 'h')
      number = idRh;
    else if (k1 == 'f')
      number = idRf;
    else if (k1 == 'g')
      number = idRg;
    else if (k1 == 'n')
      number = idRn;
    else if (k1 == 'u')
      number = idRu;
    break;
  }
  case ('S'):
  {
    if (k1 == 'b')
      number = idSb;
    else if (k1 == 'c')
      number = idSc;
    else if (k1 == 'e')
      number = idSe;
    else if (k1 == 'g')
      number = idSg;
    else if (k1 == 'i')
      number = idSi;
    else if (k1 == 'm')
      number = idSm;
    else if (k1 == 'n')
      number = idSn;
    else if (k1 == 'r')
      number = idSr;
    else
      number = id_S;
    break;
  }
  case ('T'):
  {
    if (k1 == 'a')
      number = idTa;
    else if (k1 == 'b')
      number = idTb;
    else if (k1 == 'c')
      number = idTc;
    else if (k1 == 'e')
      number = idTe;
    else if (k1 == 'h')
      number = idTh;
    else if (k1 == 'i')
      number = idTi;
    else if (k1 == 'l')
      number = idTl;
    else if (k1 == 'm')
      number = idTm;
    else if (k1 == 's')
      number = idTs;
    break;
  }
  case ('U'):
  {
    /*
    if(k1 == 'u' && k2 == 'n') number = 119;  cast heavy element numbers 'Uu /
    else if (k1 == 'b') ;
    else
    */
    number = id_U;
    break;
  }
  case ('V'):
  {
    number = id_V;
    break;
  }
  case ('W'):
  {
    number = id_W;
    break;
  }
  case ('X'):
  {
    if (k1 == 'e')
      number = idXe;
    break;
  }
  case ('Y'):
  {
    if (k1 == 'b')
      number = idYb;
    else
      number = id_Y;
    break;
  }
  case ('Z'):
  {
    if (k1 == 'r')
      number = idZr;
    break;
  }
  default:
    break;
  }
  return number;
}

vtkStdString Elements::GetElementSymbol(vtkIdType id)
{
  vtkStdString res(*Symbol);
  if(id >= 0 && id < idNumberOfElements) 
  res = Symbol[id];
  return res;
}