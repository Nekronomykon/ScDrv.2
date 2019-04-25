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

  void Render(vtkRenderer*, vtkActor*) override;

protected:
  explicit MapperCriticalPoints() = default;
  ~MapperCriticalPoints() override = default;

private:
  MapperCriticalPoints(const MapperCriticalPoints &) = delete;
  void operator=(const MapperCriticalPoints &) = delete;

  // data: Atomic;
  vtkNew<vtkGlyph3DMapper> glyphMapACP_;
  vtkSmartPointer<vtkPolyDataMapper> polyDataACP_;
  // data: Bonds;
  vtkNew<vtkGlyph3DMapper> glyphMapBCP_;
  vtkSmartPointer<vtkPolyDataMapper> polyDataBCP_;
  // data: Rings;
  vtkNew<vtkGlyph3DMapper> glyphMapRCP_;
  vtkSmartPointer<vtkPolyDataMapper> polyDataRCP_;
  // data: Cages;
  vtkNew<vtkGlyph3DMapper> glyphMapCCP_;
  vtkSmartPointer<vtkPolyDataMapper> polyDataCCP_;
};

}; // namespace vtk

#endif // !MapperCriticalPoints_h
