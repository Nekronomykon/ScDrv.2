#ifndef MapperCriticalPoints_h
#define MapperCriticalPoints_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork
  Module:    MapperCriticalPoints.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MapperCriticalPoints
 * @brief   Mapper that draws vtkMolecule objects
 *
 *
 * MapperCriticalPoints uses glyphs (display lists) to quickly render a
 * molecular field critical point structure associated with a molecule.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkNew.h>          // For vtkNew<>
#include <vtkSmartPointer.h> // For vtkSmartPointer<>

#include <vtkMapper.h>

class CriticalPoints;
class vtkGlyph3DMapper;
class vtkPolyDataMapper;

namespace vtk
{
class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MapperCriticalPoints
    : public vtkMapper
{
public:
  static MapperCriticalPoints *New();
  vtkTypeMacro(MapperCriticalPoints, vtkMapper);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  void SetInputData(CriticalPoints*);
  CriticalPoints*GetInput();

  void RenderGlyph(vtkRenderer *, vtkActor *);

  void Render(vtkRenderer*, vtkActor*) override;

  //@{
  /**
     * Get/Set the color of the atom as an rgb tuple.
     * Default: {50, 50, 50} (dark grey)
     */
  vtkGetVector3Macro(AtomColor, unsigned char);
  vtkSetVector3Macro(AtomColor, unsigned char);
  //@}

  //@{
  /**
     * Get/Set the color of the bond CPs and paths as an rgb tuple.
     * Default: {50, 50, 50} (dark grey)
     */
  vtkGetVector3Macro(BondColor, unsigned char);
  vtkSetVector3Macro(BondColor, unsigned char);
  //@}

  //@{
  /**
     * Get/Set the color of the ring CPs and paths as an rgb tuple.
     * Default: {255, 255, 255} (white)
     */
  vtkGetVector3Macro(RingColor, unsigned char);
  vtkSetVector3Macro(RingColor, unsigned char);
  //@}

  //@{
  /**
     * Get/Set the color of the cage CPs and paths as an rgb tuple.
     * Default: {255, 255, 255} (white)
     */
  vtkGetVector3Macro(CageColor, unsigned char);
  vtkSetVector3Macro(CageColor, unsigned char);
  //@}

protected:
  explicit MapperCriticalPoints() = default;
  ~MapperCriticalPoints() override = default;

private:
  MapperCriticalPoints(const MapperCriticalPoints &) = delete;
  void operator=(const MapperCriticalPoints &) = delete;

  // data: Atomic;
  unsigned char AtomColor[3];
  vtkNew<vtkGlyph3DMapper> glyphMapACP_; /* sphere / dodekahedron? */
  vtkSmartPointer<vtkPolyDataMapper> polyDataACP_;
  // data: Bonds;
  unsigned char BondColor[3];
  vtkNew<vtkGlyph3DMapper> glyphMapBCP_; /* cylinder ? cone */
  vtkSmartPointer<vtkPolyDataMapper> polyDataBCP_;
  // data: Rings;
  unsigned char RingColor[3];
  vtkNew<vtkGlyph3DMapper> glyphMapRCP_; /* disc ? cylinder */
  vtkSmartPointer<vtkPolyDataMapper> polyDataRCP_;
  // data: Cages;
  unsigned char CageColor[3];
  vtkNew<vtkGlyph3DMapper> glyphMapCCP_; /* octahedron? */
  vtkSmartPointer<vtkPolyDataMapper> polyDataCCP_;
};

}; // namespace vtk

#endif // !MapperCriticalPoints_h
