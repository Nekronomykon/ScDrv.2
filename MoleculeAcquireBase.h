#ifndef __MoleculeAcquireBase_h__
#define __MoleculeAcquireBase_h__

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    MoleculeAcquireBase.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeAcquireBase
 * @brief   Superclass for algorithms that operate on
 * vtkMolecules
 *
 * MoleculeAcquireBase is a convenience class to make writing algorithms
 * easier. There are some assumptions and defaults made by this class you
 * should be aware of. This class defaults such that your filter will have
 * one input port and one output port. If that is not the case simply change
 * it with SetNumberOfInputPorts etc. See this class constructor for the
 * default. This class also provides a FillInputPortInfo method that by
 * default says that all inputs will be vtkMolecules. If that isn't the case
 * then please override this method in your subclass. You should implement
 * the subclass's algorithm into RequestData( request, inputVec, outputVec).
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkAlgorithm.h>

class vtkDataSet;
class vtkMolecule;
class MolecularStructure;

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MoleculeAcquireBase : public vtkAlgorithm
{
protected:
  typedef vtkMolecule Molecule;
  // typedef MolecularStructure Molecule;
public:
  static MoleculeAcquireBase *New();
  vtkTypeMacro(MoleculeAcquireBase, vtkAlgorithm);
  void PrintSelf(ostream &os, vtkIndent indent) VTK_OVERRIDE;

  vtkIdType GetNumberOfAtoms() const { return NumberOfAtoms_; }
  virtual vtkIdType SetNumberOfAtoms(vtkIdType nnew)
  {
    if(nnew != this->GetNumberOfAtoms())
    {
      std::swap(NumberOfAtoms_, nnew);
      this->Modified();
    }
    return nnew;
  }

  //@{
  /**
   * Get the output data object for a port on this algorithm.
   */
  Molecule *GetOutput();
  Molecule *GetOutput(int);
  virtual void SetOutput(Molecule *d);
  //@}

  /**
   * see vtkAlgorithm for details
   */
  int ProcessRequest(vtkInformation *,
    vtkInformationVector **,
    vtkInformationVector *) VTK_OVERRIDE;

  // this method is not recommended for use, but lots of old style filters
  // use it
  vtkDataObject *GetInput();
  vtkDataObject *GetInput(int port);
  Molecule *GetMoleculeInput(int port);

  //@{
  /**
   * Set an input of this algorithm. You should not override these
   * methods because they are not the only way to connect a pipeline.
   * Note that these methods support old-style pipeline connections.
   * When writing new code you should use the more general
   * vtkAlgorithm::SetInputConnection().  These methods transform the
   * input index to the input port index, not an index of a connection
   * within a single port.
   */
  void SetInputData(vtkDataObject *);
  void SetInputData(int, vtkDataObject *);
  //@}

  //@{
  /**
   * Add an input of this algorithm.  Note that these methods support
   * old-style pipeline connections.  When writing new code you should
   * use the more general vtkAlgorithm::AddInputConnection().  See
   * SetInputData() for details.
   */
  void AddInputData(vtkDataObject *);
  void AddInputData(int, vtkDataObject *);
  //@}

protected:
  MoleculeAcquireBase();
  ~MoleculeAcquireBase() VTK_OVERRIDE;

  // convenience method
  virtual int RequestInformation(vtkInformation *request,
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);

  /**
   * This is called by the superclass.
   * This is the method you should override.
   */
  virtual int RequestData(vtkInformation *request,
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);

  /**
   * This is called by the superclass.
   * This is the method you should override.
   */
  virtual int RequestUpdateExtent(vtkInformation *,
    vtkInformationVector **,
    vtkInformationVector *);

  // see algorithm for more info
  int FillOutputPortInformation(int port, vtkInformation *info) VTK_OVERRIDE;
  int FillInputPortInformation(int port, vtkInformation *info) VTK_OVERRIDE;

private:
  MoleculeAcquireBase(const MoleculeAcquireBase &) VTK_DELETE_FUNCTION;
  void operator=(const MoleculeAcquireBase &) VTK_DELETE_FUNCTION;

  //----------------------------------------------------------------------------
  vtkIdType NumberOfAtoms_;
};

#endif // !__MoleculeAcquireBase_h__
