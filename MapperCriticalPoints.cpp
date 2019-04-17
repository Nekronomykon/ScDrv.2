#include "MapperCriticalPoints.h"

using namespace vtk;
using namespace std;

// Note this class may have an accelerated subclass ala
// MapperCriticalPointsOpenGL. If you change this class please
// also check that class for impacts.
//----------------------------------------------------------------------------
vtkStandardNewMacro(MapperCriticalPoints);

//----------------------------------------------------------------------------
MapperCriticalPoints::MapperCriticalPoints()
{
}

//----------------------------------------------------------------------------
MapperCriticalPoints::~MapperCriticalPoints() {}

//----------------------------------------------------------------------------
void MapperCriticalPoints::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}