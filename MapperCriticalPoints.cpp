#include "MapperCriticalPoints.h"

using namespace vtk;
using namespace std;

#include <vtkExecutive.h>

#include <vtkGlyph3DMapper.h>

#include <vtkCubeSource.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkRegularPolygonSource.h>

#include "CriticalPoints.h"

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
void MapperCriticalPoints::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}


//----------------------------------------------------------------------------
void MapperCriticalPoints::SetInputData(CriticalPoints *input)
{
  this->SetInputDataInternal(0, input);
}

//----------------------------------------------------------------------------
CriticalPoints *MapperCriticalPoints::GetInput()
{
  return CriticalPoints::SafeDownCast(this->GetExecutive()->GetInputData(0, 0));
}


//----------------------------------------------------------------------------
void MapperCriticalPoints::Render(vtkRenderer*, vtkActor*)
{
  
}