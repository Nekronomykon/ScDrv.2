#ifndef Command_PickSubstructure_h
#define Command_PickSubstructure_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkCommand.h>

class CommandPickSubstructure
: public vtkCommand
{
public:
  static CommandPickSubstructure *New();
  vtkTypeMacro(CommandPickSubstructure, vtkCommand);
  void PrintSelf(ostream& os, vtkIndent indent) override;

// Adjust that
  void Execute(vtkObject *, unsigned long, void *) override;

protected:
  CommandPickSubstructure();
  ~CommandPickSubstructure() override;
};

#endif // !Command_PickSubstructure_h
