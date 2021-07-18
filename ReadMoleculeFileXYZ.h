#ifndef __Read_MoleculeFile_XYZ_h
#define __Read_MoleculeFile_XYZ_h

#ifdef _MSC_VER
#  pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkXYZMolReader2.h>

#include "ReadMoleculeFileBase.h"

namespace vtk {
class /* VTKIOCHEMISTRY_EXPORT */ ReadMoleculeFileXYZ
  : public ReadMoleculeFileBase
{
public:
  static ReadMoleculeFileXYZ* New();
  vtkTypeMacro(ReadMoleculeFileXYZ, ReadMoleculeFileBase);
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
  ReadMoleculeFileXYZ();
  ~ReadMoleculeFileXYZ() override = default;

  int RequestData(vtkInformation*, vtkInformationVector**,
                  vtkInformationVector*) override;
  int RequestInformation(vtkInformation*, vtkInformationVector**,
                         vtkInformationVector*) override;

  std::string FileName = "";
  std::vector<istream::pos_type>
    FilePositions; // to store beginning of each step
  std::vector<double> TimeSteps;

private:
  ReadMoleculeFileXYZ(const ReadMoleculeFileXYZ&) = delete;
  void operator=(const ReadMoleculeFileXYZ&) = delete;
};

};

#endif //!__Read_MoleculeFile_XYZ_h
