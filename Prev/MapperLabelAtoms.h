#ifndef Label_Atoms_h
#define Label_Atoms_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork
  Module:    vtkLabeledDataMapper.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtk::MapperLabelAtoms
 * @brief   draw text labels at dataset points
 *
 * MapperLabelAtoms is inherited from vtkLabeledDataMapper, that is in it case
 * a mapper that renders text at dataset
 * points. Various items can be labeled including point ids, scalars,
 * vectors, normals, texture coordinates, tensors, and field data components.
 *
 * The format with which the label is drawn is specified using a
 * printf style format string. The font attributes of the text can
 * be set through the vtkTextProperty associated to this mapper.
 *
 * By default, all the components of multi-component data such as
 * vectors, normals, texture coordinates, tensors, and multi-component
 * scalars are labeled. However, you can specify a single component if
 * you prefer. (Note: the label format specifies the format to use for
 * a single component. The label is creating by looping over all components
 * and using the label format to render each component.)
 * The character separator between components can be set. By default,
 * it is set to a single whitespace.
 *
 * @warning
 * Use this filter in combination with vtkSelectVisiblePoints if you want
 * to label only points that are visible. If you want to label cells rather
 * than points, use the filter vtkCellCenters to generate points at the
 * center of the cells. Also, you can use the class vtkIdFilter to
 * generate ids as scalars or field data, which can then be labeled.
 *
 * @sa
 * vtkMapper2D vtkActor2D vtkTextMapper vtkTextProperty vtkSelectVisiblePoints
 * vtkIdFilter vtkCellCenters
*/

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkNew.h>          // For vtkNew<>
#include <vtkSmartPointer.h> // For vtkSmartPointer<>

// to avoid "error: expected constructor, destructor, or type conversion before ‘;’ token"
// vtkStandardNewMacro(className);
#include <vtkObjectFactory.h> 

#include <vtkLabeledDataMapper.h>

namespace vtk
{
class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MapperLabelAtoms
    : public vtkLabeledDataMapper
{
public:
  static MapperLabelAtoms *New();
  vtkTypeMacro(MapperLabelAtoms, vtkLabeledDataMapper);
  void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
  MapperLabelAtoms();
  ~MapperLabelAtoms() override = default;

private:
  MapperLabelAtoms(const MapperLabelAtoms &) = delete;
  void operator=(const MapperLabelAtoms &) = delete;
};

}; // namespace vtk

#endif // !Label_Atoms_h
