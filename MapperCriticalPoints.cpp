#include "MapperCriticalPoints.h"

using namespace vtk;
using namespace std;

#include <vtkGlyph3DMapper.h>

#include "CriticalPoints.h"

// Note this class may have an accelerated subclass ala
// MapperCriticalPointsOpenGL. If you change this class please
// also check that class for impacts.
//----------------------------------------------------------------------------
vtkStandardNewMacro(MapperCriticalPoints);

//----------------------------------------------------------------------------
void MapperCriticalPoints::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

void MapperCriticalPoints::Render(vtkRenderer*, vtkActor*)
{}