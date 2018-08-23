#ifndef MODELMOLECULARBONDSET_H
#define MODELMOLECULARBONDSET_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QAbstractTableModel>

class ModelMolecularBondset
    : public QAbstractTableModel
{
public:
  explicit ModelMolecularBondset();
};

#endif // MODELMOLECULARBONDSET_H
