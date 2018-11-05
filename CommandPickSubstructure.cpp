#include "CommandPickSubstructure.h"


//----------------------------------------------------------------------------
vtkStandardNewMacro(CommandPickSubstructure);

//----------------------------------------------------------------------------
CommandPickSubstructure::CommandPickSubstructure()
{

}

//----------------------------------------------------------------------------
CommandPickSubstructure::~CommandPickSubstructure()
{

}

//----------------------------------------------------------------------------
void CommandPickSubstructure::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass->PrinsSelf(os, indent);
}

//----------------------------------------------------------------------------
void CommandPickSubstructure::Execute(vtkObject *, unsigned long, void *)
{}