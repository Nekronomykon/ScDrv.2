#ifndef QVTK_MoleculeWidget_h
#define QVTK_MoleculeWidget_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork Copy
  Module:    QVTKMoleculeWidget.h
  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.

   This software is distributed WITHOUT ANY WARRANTY; without even
   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkColor.h>
#include <vtkStdString.h>
#include <vtkMolecule.h>

#include <vtkInteractorStyle.h>
#include <vtkAreaPicker.h>

#include "MoleculeMapper.h"
#include "CommandPickFragment.h"

#include "MoleculeMapperStyle.h"

class vtkLabelPlacementMapper;

namespace vtk
{

class QVTKMoleculeWidget
    : public QVTKOpenGLNativeWidget
// : public QVTKOpenGLWidget
{
  Q_OBJECT
public:
  typedef vtkColor3d BgColorType;

  typedef QVTKOpenGLNativeWidget BaseWidget;
  // typedef QVTKOpenGLWidget BaseWidget;
  explicit QVTKMoleculeWidget(QWidget * /*parent*/ = nullptr);
  ~QVTKMoleculeWidget() override = default;

  typedef vtkSmartPointer<vtkInteractorStyle> InteractorStyle;

protected:
public:
  void ShowMolecule(vtkMolecule * /*pMol*/ = nullptr);
  void doRender();

  vtkRenderer *GetRenderer() const { return renderer_; }
  vtkCamera *GetActiveCamera() { return !renderer_ ? nullptr : renderer_->GetActiveCamera(); }
  MoleculeMapper *GetMoleculeMapper() const { return mol_mapper_; }

  void SetMoleculeSpaceFill()
  {
    mol_mapper_->UseSpaceFillSettings();
    this->doRender();
  }
  void SetMoleculeBallsSticks()
  {
    mol_mapper_->UseBallAndStickSettings();
    this->doRender();
  }
  void SetMoleculeSticksOnly()
  {
    mol_mapper_->UseSticksOnlySettings();
    this->doRender();
  }
  void SetMoleculeFastRender()
  {
    mol_mapper_->UseFastRenderSettings();
    this->doRender();
  }

  bool MoleculeIsSpaceFill() const { return mol_mapper_->IsSetSpaceFill(); }
  bool MoleculeIsBallsSticks() const { return mol_mapper_->IsSetBallsSticks(); }
  bool MoleculeIsSticks() const { return mol_mapper_->IsSetSticksOnly(); }
  bool MoleculeIsFast() const { return mol_mapper_->IsSetFastRender(); }

  BgColorType &backgroundColor() { return bgColor_; }

private:
  typedef vtkSmartPointer<vtkActor> Actor;
  typedef vtkSmartPointer<MoleculeMapper> MolMapper;
  typedef vtkSmartPointer<vtkLabelPlacementMapper> LabelMapper;
  typedef vtkSmartPointer<vtkRenderer> Renderer;
  typedef vtkSmartPointer<vtkAreaPicker> AreaPicker;

private:
  Renderer renderer_;
  BgColorType bgColor_;
  MolMapper mol_mapper_;
  LabelMapper labelAtoms_;
  LabelMapper labelBonds_;
  AreaPicker area_picker_;
  InteractorStyle styleInteractor_;
  vtkNew<CommandPickFragment> cmdPickFragment_;
};

}; // namespace vtk

#endif // !QVTK_MoleculeWidget_h
