#ifndef __QVTK_MoleculeWidget_h__
#define __QVTK_MoleculeWidget_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

/*=========================================================================

  Program:   Visualization Toolkit Local Fork Copy
  Module:    QVTKMoleculeWidget.h
  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

   This software is distributed WITHOUT ANY WARRANTY; without even
   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLSimpleWidget.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkMolecule.h>
#include <vtkMoleculeMapper.h>

#include "QVTKMoleculeMapStyle.h"

class QVTKMoleculeWidget
    : public QVTKOpenGLWidget
{
  Q_OBJECT
public:
  QVTKMoleculeWidget(QWidget * /*parent*/ = Q_NULLPTR);
  ~QVTKMoleculeWidget() override;

public:
  void ShowMolecule(vtkMolecule * /*pMol*/ = nullptr);

private:
  typedef vtkSmartPointer<vtkActor> Actor;
  typedef vtkSmartPointer<vtkMoleculeMapper> MolMapper;
  typedef vtkSmartPointer<vtkRenderer> Renderer;

private:
  MolMapper mol_mapper_;
  QVTKMoleculeMapStyle mol_style_;

  static const QVTKMoleculeMapStyle style_VdW;
  static const QVTKMoleculeMapStyle style_BnS;
  static const QVTKMoleculeMapStyle style_Fast;
  static const QVTKMoleculeMapStyle style_Sticks;
};

#endif // !__QVTK_MoleculeWidget_h__
