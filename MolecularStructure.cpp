#include "MolecularStructure.h"

MolecularStructure::MolecularStructure()
{

}

MolecularStructure::~MolecularStructure()
{
  the_molecule_->Initialize();
}
