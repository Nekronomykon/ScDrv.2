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
/*********************************************************************************
  Traits specs:
**********************************************************************************/

struct TraitsBase
{
  static const double AngstromInBohr;
  static size_t MeasureStringGroup(std::istream& in)
  {
    std::string str_line;
    if (!in || !std::getline(in, str_line)) return 0;

    size_t nRes = 0;
    do {
      if (str_line.empty()) break;
      ++nRes;
    } while (std::getline(in, str_line));
    return nRes;
  }
};


/*********************************************************************************
  XMol XYZ format:
  (CHAR)SYMBOL X Y Z
**********************************************************************************/

template<class T>
struct TraitsSymbolicXYZ : TraitsBase
{
  template<typename Molecule>
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
      if (!(ssinp >> atomType >> x >> y >> z))
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

template<class T>
struct TraitsNumericXYZ : TraitsBase
{
  template<typename Molecule>
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
template<class T>
struct TraitsLabelNumberXYZ : TraitsBase
{
  template<typename Molecule>
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


template<class T>
struct TraitsCentreWFN : TraitsBase
{
  template<typename Molecule>
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

      mol->AppendAtom(atomType, x, y, z);
      // mol->LabelAtom(i, label);
    }
    return 0;
  }
};

#endif // !__Traits_AcquireAtoms_h__
