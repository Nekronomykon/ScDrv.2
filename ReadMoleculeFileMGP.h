#ifndef __ReadMolecule_File_MGP_h
#define __ReadMolecule_File_MGP_h

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include "ReadMoleculeFileBase.h"

namespace vtk {

class /* VTKIOCHEMISTRY_EXPORT */ ReadMoleculeFileMGP
  : public ReadMoleculeFileBase
{
private:
  /* data */
public:
  static ReadMoleculeFileMGP* New();
  vtkTypeMacro(ReadMoleculeFileMGP, ReadMoleculeFileBase);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Get/Set the name of the XYZ Molecule file
   */
  vtkSetStdStringFromCharMacro(FileName);
  vtkGetCharFromStdStringMacro(FileName);
  ///@}
protected:
  ReadMoleculeFileMGP(/* args */);
  ~ReadMoleculeFileMGP() override = default;
};

};

#endif // !__ReadMolecule_File_MGP_h