#ifndef Command_PickFragment_h
#define Command_PickFragment_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkCommand.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkObject.h>
#include <vtkSetGet.h>
#include <vtkIdTypeArray.h>
#include <vtkAreaPicker.h>
#include <vtkRenderer.h>
#include <vtkSelection.h>
#include <vtkMolecule.h>
#include <vtkMoleculeMapper.h>

class CommandPickFragment
    : public vtkCommand
{
public:
  static CommandPickFragment *New() { return new CommandPickFragment; }
  vtkTypeMacro(CommandPickFragment, vtkCommand);
  // void PrintSelf(ostream& os, vtkIndent indent) override;

  // Adjust that
  void Execute(vtkObject *caller, unsigned long eventId,
               void *callData) override;

  vtkIdTypeArray *GetSelectedAtomsIndex() const { return idxAtoms_.Get(); }
  vtkIdTypeArray *GetSelectedBondsIndex() const { return idxBonds_.Get(); }

  vtkRenderer *GetRenderer() const { return ptrRenderer_; }
  vtkRenderer *ResetRenderer(vtkRenderer *ptr)
  {
    if (ptr != ptrRenderer_)
      std::swap(ptr, ptrRenderer_);
    return ptr;
  }

  vtkAreaPicker *GetAreaPicker() const { return ptrAreaPicker_; }
  vtkAreaPicker *ResetAreaPicker(vtkAreaPicker *ptr)
  {
    if (ptr != ptrAreaPicker_)
      std::swap(ptr, ptrAreaPicker_);
    return ptr;
  }

  vtkMoleculeMapper *GetMoleculeMapper() const { return ptrMoleculeMapper_; }
  vtkMoleculeMapper *ResetMoleculeMapper(vtkMoleculeMapper *ptr)
  {
    if (ptr != ptrMoleculeMapper_)
      std::swap(ptr, ptrMoleculeMapper_);
    return ptr;
  }

  void SetIdArrays(vtkSelection *sel)
  {
    this->GetMoleculeMapper()->GetSelectedAtomsAndBonds(sel, this->GetSelectedAtomsIndex(), this->GetSelectedBondsIndex());
  }

protected:
  CommandPickFragment() = default;
  ~CommandPickFragment() override = default;

private:
  // selection index:
  vtkNew<vtkIdTypeArray> idxAtoms_;
  vtkNew<vtkIdTypeArray> idxBonds_;
  // temporary
  vtkRenderer *ptrRenderer_;
  vtkAreaPicker *ptrAreaPicker_;
  vtkMoleculeMapper *ptrMoleculeMapper_;
};

#endif // !Command_PickFragment_h
