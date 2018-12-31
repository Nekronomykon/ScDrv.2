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

#include <vtkColor.h>
#include <vtkStdString.h>
#include <vtkMolecule.h>
#include <vtkMoleculeMapper.h>

#include <vtkInteractorStyle.h>
#include <vtkAreaPicker.h>
#include "CommandPickFragment.h"

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
  typedef vtkSmartPointer<vtkInteractorStyle> InteractorStyle;

  static MolStyle styleFast();
  static MolStyle styleFill();
  static MolStyle styleBall();
  static MolStyle styleBond();

protected:
  static vtkStdString name_default_background;

  void AdjustBackgroundColor(void);

public:
  void ShowMolecule(vtkMolecule * /*pMol*/ = nullptr);
  bool resetStyle(const QVTKMoleculeMapStyle & /*style*/);
  void doRender();

  vtkRenderer* GetRenderer() const { return renderer_; }

  static vtkStdString GetDefaultBackgroundColorName();
  static vtkStdString ResetDefaultBackgroundColorName(vtkStdString name_new);

  vtkStdString GetBackgroundColorName() const;
  vtkStdString ResetBackgroundColorName(vtkStdString name_new);

  bool moleculeInBallsSticks() const;
  bool moleculeInSpaceFill() const;
  bool moleculeInFastRender() const;
  bool moleculeInSticks() const;

private:
  typedef vtkSmartPointer<vtkActor> Actor;
  typedef vtkSmartPointer<vtkMoleculeMapper> MolMapper;
  typedef vtkSmartPointer<vtkRenderer> Renderer;
  typedef vtkSmartPointer<vtkAreaPicker> AreaPicker;

private:
  Renderer renderer_;
  vtkStdString name_background_;
  vtkColor3d bgColor_;
  MolMapper mol_mapper_;
  MolStyle mol_style_;
  AreaPicker area_picker_;
  InteractorStyle styleInteractor_;
  vtkNew<CommandPickFragment> cmdPickFragment_;

  static const MolStyle style_VdW;
  static const MolStyle style_BnS;
  static const MolStyle style_Fast;
  static const MolStyle style_Sticks;
};

#endif // !QVTK_MoleculeWidget_h
