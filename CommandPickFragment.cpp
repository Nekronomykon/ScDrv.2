#include "CommandPickFragment.h"

#include <vtkProp3DCollection.h>
#include <vtkHardwareSelector.h>

#include <QString>
#include <QMessageBox>

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
    // vtkSmartPointer<vtkSelection> result (selector->Select());
    vtkSelection* result(selector->Select());
    this->SetIdArrays(result);
    this->DumpMolSelection();
    result->Delete();
  }
}

inline void CommandPickFragment::SetIdArrays(vtkSelection * sel)
{
  this->GetMoleculeMapper()->GetSelectedAtomsAndBonds(sel
    , this->IndexSelectedAtoms() // vertex
    , this->IndexSelectedBonds() // edge
  );
}

void CommandPickFragment::DumpMolSelection()
{
  vtkMolecule *mol = this->GetMoleculeMapper()->GetInput();

  // Print selection
  ostringstream osel;
  osel << " :: Selection ::"
    << endl << "[Atoms]: " << this->IndexSelectedAtoms()->GetNumberOfTuples() << "::" << endl;
  for (vtkIdType i = 0; i < this->IndexSelectedAtoms()->GetNumberOfTuples(); i++)
  {
    osel << this->IndexSelectedAtoms()->GetValue(i) + 1 << "; ";
  }
  osel << endl << "[Bonds]: " << this->IndexSelectedBonds()->GetNumberOfTuples() << "::" << endl;
  for (vtkIdType i = 0; i < this->IndexSelectedBonds()->GetNumberOfTuples(); i++)
  {
    vtkBond bond = mol->GetBond(this->IndexSelectedBonds()->GetValue(i));
    osel << bond.GetId() << ":(" << bond.GetBeginAtomId() << "--"
      << bond.GetEndAtomId() << ");";
  }
  osel << endl << flush;
  QMessageBox::information(nullptr
    , QString("Selection")
    , QString(osel.str().c_str())
  );
}
