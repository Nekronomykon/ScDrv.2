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
#include <vtkCamera.h>
#include <vtkNamedColors.h>

#include <vtkInteractorStyle.h>
#include <vtkAreaPicker.h>

#include <vtkMolecule.h>
/// here, the end of reforms ;)

#include "MapperMolecule.h"
#include "MapperCriticalPoints.h"

#include "CommandPickFragment.h"

#include "MoleculeMapperStyle.h"

// class vtkLabelPlacementMapper;
class vtkLabeledDataMapper;
class vtkActor;
class vtkActor2D;

namespace vtk
{

class QVTKMoleculeWidget
    : public QVTKOpenGLNativeWidget
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
  void doRender();

public:
  void ShowMolecule(vtkMolecule * /*pMol*/ = nullptr);
  bool isProjectOrthogonal()  const { return  isProjectOrthogonal_; }
  bool isProjectPerspective() const { return !isProjectOrthogonal_; }

  vtkRenderer *GetRenderer() const { return renderer_; }
  vtkCamera *GetActiveCamera() { return !renderer_ ? nullptr : renderer_->GetActiveCamera(); }
  MapperMolecule *GetMoleculeMapper() const { return mapMolecule_; }

  bool BackgroundColorByNameAt(vtkStdString name, vtkNamedColors*);

  void SetMoleculeSpaceFill()
  {
    mapMolecule_->UseSpaceFillSettings();
    this->doRender();
  }
  void SetMoleculeBallsSticks()
  {
    mapMolecule_->UseBallAndStickSettings();
    this->doRender();
  }
  void SetMoleculeSticksOnly()
  {
    mapMolecule_->UseSticksOnlySettings();
    this->doRender();
  }
  void SetMoleculeFastRender()
  {
    mapMolecule_->UseFastRenderSettings();
    this->doRender();
  }

  bool MoleculeIsSpaceFill() const { return mapMolecule_->IsSetSpaceFill(); }
  bool MoleculeIsBallsSticks() const { return mapMolecule_->IsSetBallsSticks(); }
  bool MoleculeIsSticks() const { return mapMolecule_->IsSetSticksOnly(); }
  bool MoleculeIsFast() const { return mapMolecule_->IsSetFastRender(); }

  void ResetMultisample(int /*idAA*/);
  void ProjectParallel(bool /* bPar  */ = true);

  BgColorType &backgroundColor() { return bgColor_; }

private:
  typedef vtkSmartPointer<vtkActor> Actor;
  typedef vtkSmartPointer<vtkActor2D> Actor2D;

  typedef vtkSmartPointer<MapperMolecule> MapMolecule;
  typedef vtkSmartPointer<MapperCriticalPoints> MapCritical;
  typedef vtkSmartPointer<vtkLabeledDataMapper> MapLabelData;

  typedef vtkSmartPointer<vtkRenderer> Renderer;

  typedef vtkSmartPointer<vtkAreaPicker> AreaPicker;
  

private:
  bool isProjectOrthogonal_ = false;
  Renderer renderer_;
  BgColorType bgColor_;
  MapMolecule mapMolecule_;
  MapCritical mapCritical_;
  MapLabelData mapDataAtoms_;
  MapLabelData mapDataBonds_;
  AreaPicker pickSelect_;
  InteractorStyle styleInteractor_;
  vtkNew<CommandPickFragment> cmdPickFragment_;
};

}; // namespace vtk

#endif // !QVTK_MoleculeWidget_h
