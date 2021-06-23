#ifndef __ReadMolecule_File_MGP_h
#define __ReadMolecule_File_MGP_h

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include "ReadMoleculeFileBase.h"

namespace vtk {

class ReadMoleculeFileMGP : public ReadMoleculeFileBase
{
private:
  /* data */
public:
protected:
  ReadMoleculeFileMGP(/* args */);
  ~ReadMoleculeFileMGP();
};

};

#endif // !__ReadMolecule_File_MGP_h