#ifndef Command_PickFragment_h
#define Command_PickFragment_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkCommand.h>

#include <vtkObject.h>
#include <vtkSetGet.h>

class CommandPickFragment
: public vtkCommand
{
public:
  static CommandPickFragment *New() { return new CommandPickFragment; }
  vtkTypeMacro(CommandPickFragment, vtkCommand);
  void PrintSelf(ostream& os, vtkIndent indent) override;

// Adjust that
  void Execute(vtkObject *caller, unsigned long eventId,
                       void *callData) override;

protected:
  CommandPickFragment() = default;
  ~CommandPickFragment() override = default;
};

#endif // !Command_PickFragment_h
