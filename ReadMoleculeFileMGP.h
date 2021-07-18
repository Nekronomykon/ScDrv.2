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
   * Get/Set the output (vtkMolecule) that the reader will fill
   */
  vtkMolecule* GetOutput();
  void SetOutput(vtkMolecule*) override;
  ///@}

  ///@{
  /**
   * Get/Set the name of the XYZ Molecule file
   */
  vtkSetStdStringFromCharMacro(FileName);
  vtkGetCharFromStdStringMacro(FileName);
  ///@}
protected:
  std::string FileName = ""; // vtkStdString???

  ReadMoleculeFileMGP();
  ~ReadMoleculeFileMGP() override = default;
};

};

#endif // !__ReadMolecule_File_MGP_h