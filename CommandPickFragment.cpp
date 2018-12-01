#include "CommandPickFragment.h"

//----------------------------------------------------------------------------
// vtkStandardNewMacro(CommandPickFragment);

//----------------------------------------------------------------------------
// void CommandPickFragment::PrintSelf(ostream& os, vtkIndent indent)
// {
// }

//----------------------------------------------------------------------------
void CommandPickFragment::Execute(vtkObject *caller, unsigned long eventId,
                                  void *callData)
{
  vtkProp3DCollection *props = this->GetAreaPicker()->GetProp3Ds();
  if (props->GetNumberOfItems() != 0)
  {
    // If anything was picked during the fast area pick, do a more detailed
    // pick.
    vtkNew<vtkHardwareSelector> selector;
    selector->SetFieldAssociation(vtkDataObject::FIELD_ASSOCIATION_POINTS);

    vtkRenderer* pR = this->GetRenderer();

    selector->SetRenderer(pR);
    selector->SetArea(
        static_cast<unsigned int>(pR->GetPickX1()),
        static_cast<unsigned int>(pR->GetPickY1()),
        static_cast<unsigned int>(pR->GetPickX2()),
        static_cast<unsigned int>(pR->GetPickY2()));
    // Make the actual pick and pass the result to the convenience function
    // defined earlier
    vtkSelection *result = selector->Select();
    this->SetIdArrays(result);
    this->DumpMolSelection();
    result->Delete();
  }
}