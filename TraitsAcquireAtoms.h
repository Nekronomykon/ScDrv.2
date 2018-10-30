#ifndef __Traits_AcquireAtoms_h__
#define __Traits_AcquireAtoms_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkPeriodicTable.h>
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
  static const double AngstromInBohr;
  static std::string ScrollEmptyStrings(std::istream &in);
  static size_t MeasureStringGroup(std::istream &in);
};

/*********************************************************************************
  XMol XYZ format:
  (CHAR)SYMBOL X Y Z
**********************************************************************************/

template <class T>
struct TraitsSymbolicXYZ : TraitsBase
{
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    vtkNew<vtkPeriodicTable> ptrTable;
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
      mol->AppendAtom(ptrTable->GetAtomicNumber(atomType.c_str()), x, y, z);
      // mol->LabelAtom(i, atomType);
    }
    return 0;
  }
};

/*********************************************************************************
  MOPAC XYZ part format:
  NUM# SYMBOL X Y Z
**********************************************************************************/

template <class T>
struct TraitsNSymbolicXYZ : TraitsBase
{
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    vtkNew<vtkPeriodicTable> ptrTable;
    std::string str_line;

    assert(mol);
    mol->Initialize();
    for (int i = 0; i < nAtoms; i++)
    {
      if (!std::getline(in, str_line) || str_line.empty())
        return ++i;

      std::istringstream ssinp(str_line);

      std::string atomType;
      float x, y, z;
      if (!(ssinp >> atomType >> atomType >> x >> y >> z))
        return -(++i);
      mol->AppendAtom(ptrTable->GetAtomicNumber(atomType.c_str()), x, y, z);
      // mol->LabelAtom(i, atomType);
    }
    return 0;
  }
};

/*********************************************************************************
  MOPAC +1 padded XYZ part format:
  NUM# SYMBOL X pad Y pad Z pad
**********************************************************************************/

template <class T>
struct TraitsSymXYZPadded : TraitsBase
{
  template <typename Molecule>
  static int AppendAtoms(std::istream &in, int nAtoms, Molecule *mol)
  {
    assert(nAtoms > 0);

    vtkNew<vtkPeriodicTable> ptrTable;
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
      mol->AppendAtom(ptrTable->GetAtomicNumber(atomType.c_str()), x, y, z);
      // mol->LabelAtom(i, atomType);
    }
    return 0;
  }
};

/*********************************************************************************
  CUBE XYZ format:
  (UNSIGNED INT)ATOM_NUM X Y Z
**********************************************************************************/

template <class T>
struct TraitsNumericXYZ : TraitsBase
{
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
template <class T>
struct TraitsLabelNumberXYZ : TraitsBase
{
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

      mol->AppendAtom(atomType,
        x * AngstromInBohr,
        y * AngstromInBohr,
        z * AngstromInBohr);
      // mol->LabelAtom(i, label);
    }
    return 0;
  }
};

#endif // !__Traits_AcquireAtoms_h__
