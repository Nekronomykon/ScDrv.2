#ifndef QVTK_MoleculeWidget_h
#define QVTK_MoleculeWidget_h

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
#include <QVTKOpenGLNativeWidget.h>

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
  typedef QVTKOpenGLWidget BaseWidget;
  explicit QVTKMoleculeWidget(QWidget * /*parent*/ = Q_NULLPTR);
  ~QVTKMoleculeWidget() override;

  typedef QVTKMoleculeMapStyle MolStyle;

  static MolStyle styleFast();
  static MolStyle styleFill();
  static MolStyle styleBall();
  static MolStyle styleBond();

public:
  void ShowMolecule(vtkMolecule * /*pMol*/ = nullptr);
  bool resetStyle(const QVTKMoleculeMapStyle & /*style*/);
  void doRender();

  bool moleculeInBallsSticks() const;
  bool moleculeInSpaceFill() const;
  bool moleculeInFastRender() const;
  bool moleculeInSticks() const;

private:
  typedef vtkSmartPointer<vtkActor> Actor;
  typedef vtkSmartPointer<vtkMoleculeMapper> MolMapper;
  typedef vtkSmartPointer<vtkRenderer> Renderer;

private:
  MolMapper mol_mapper_;
  MolStyle mol_style_;

  static const MolStyle style_VdW;
  static const MolStyle style_BnS;
  static const MolStyle style_Fast;
  static const MolStyle style_Sticks;
};

#endif // !QVTK_MoleculeWidget_h
