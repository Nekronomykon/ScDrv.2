#ifndef MoleculeMapper_OpenGL_h
#define MoleculeMapper_OpenGL_h

/*=========================================================================

  Program:   Visualization Toolkit

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MoleculeMapperOpenGL
 * @brief   An accelerated class for rendering molecules
 *
 * A MoleculeMapper that uses imposters to do the rendering. It uses
 * vtkOpenGLSphereMapper and vtkOpenGLStickMapper to do the rendering.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryOpenGL2Module.h" // For export macro
#include "MoleculeMapper.h"
#include <vtkNew.h> // For vtkNew

class vtkOpenGLSphereMapper;
class vtkOpenGLStickMapper;

namespace vtk {

class /*VTKDOMAINSCHEMISTRYOPENGL2_EXPORT*/ MoleculeMapperOpenGL
  : public MoleculeMapper
{
public:
  static MoleculeMapperOpenGL* New();
  vtkTypeMacro(MoleculeMapperOpenGL, MoleculeMapper)

  //@{
  /**
   * Reimplemented from base class
   */
  void Render(vtkRenderer *, vtkActor *) override;
  void ReleaseGraphicsResources(vtkWindow *) override;
  //@}

  /**
   * provide access to the underlying mappers
   */
  vtkOpenGLSphereMapper *GetFastAtomMapper() {return this->FastAtomMapper; }
  vtkOpenGLStickMapper  *GetFastBondMapper() {return this->FastBondMapper; }
  /**
   * allows a mapper to update a selections color buffers
   * Called from a prop which in turn is called from the selector
   */
  void ProcessSelectorPixelBuffers(vtkHardwareSelector *sel,
    std::vector<unsigned int> &pixeloffsets,
    vtkProp *prop) override;

protected:
  MoleculeMapperOpenGL();
  ~MoleculeMapperOpenGL() override = default;

  void UpdateAtomGlyphPolyData() override;
  void UpdateBondGlyphPolyData() override;

  //@{
  /**
   * Internal mappers
   */
  vtkNew<vtkOpenGLSphereMapper> FastAtomMapper;
  vtkNew<vtkOpenGLStickMapper> FastBondMapper;
  //@}

private:
  MoleculeMapperOpenGL(const MoleculeMapperOpenGL&) = delete;
  void operator=(const MoleculeMapperOpenGL&) = delete;
};

} // namespace vtk

#endif // !MoleculeMapper_OpenGL_h
