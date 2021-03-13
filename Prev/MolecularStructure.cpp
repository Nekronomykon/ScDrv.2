#include "MolecularStructure.h"

MolecularStructure::MolecularStructure()
  : molecule_(Molecule::New())
  , bonds_build_(BuildBonds::New())
  , idxSelectedAtoms_(IndexArray::New())
  , idxSelectedBonds_(IndexArray::New())
{}

MolecularStructure::~MolecularStructure()
{}

vtkMolecule* MolecularStructure::Initialize()
{
  idxSelectedAtoms_->Initialize();
  idxSelectedBonds_->Initialize();
  molecule_->Initialize();
  return molecule_;
}

vtkMolecule *MolecularStructure::getMolecule() const { return static_cast<vtkMolecule *>(molecule_); }

vtkMolecule *MolecularStructure::operator->() const { return this->getMolecule(); }

MolecularStructure::operator vtkMolecule *() const { return this->getMolecule(); }

vtkIdType MolecularStructure::UpdateBonds()
{
  bonds_build_->RemoveAllInputs();
  bonds_build_->SetInputData(molecule_);
  NewMolecule mol_bound;
  bonds_build_->SetOutput(mol_bound);
  bonds_build_->Update();
  molecule_->DeepCopy(mol_bound);
  return molecule_->GetNumberOfBonds();
}

vtkStdString MolecularStructure::GetTitle() const
{
  return title_;
}

vtkStdString MolecularStructure::ResetTitle(vtkStdString title)
{
  std::swap(title_, title);
  return title;
}
