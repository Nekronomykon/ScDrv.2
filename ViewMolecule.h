#ifndef View_Molecule__h
#define View_Molecule__h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>

#include <QVTKOpenGLNativeWidget.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkStdString.h>

#include <vtkColor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLRenderWindow.h>

#include "StyleMapMolecule.h"
#include <vtkMoleculeMapper.h>

#include <vtkInteractorStyleTrackballCamera.h>

using namespace vtk;

typedef vtkNew<vtkActor> NewActor;
typedef vtkSmartPointer<vtkActor> AnActor;

typedef vtkNew<vtkRenderer> NewRender;
typedef vtkSmartPointer<vtkRenderer> ARender;

typedef vtkNew<vtkMoleculeMapper> NewMapMol;
typedef vtkSmartPointer<vtkMoleculeMapper> AMapMol;

typedef vtkNew<vtkInteractorStyleTrackballCamera> NewInStyTrkCamera;
typedef vtkSmartPointer<vtkInteractorStyleTrackballCamera> AnInStyTrkCamera;

class ViewMolecule
    : public QVTKOpenGLNativeWidget
{
  Q_OBJECT
  typedef QVTKOpenGLNativeWidget Superclass;

public:
  ViewMolecule(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
  ~ViewMolecule() override = default;

  void doRender();
  void adjustBgColor();
  void setBgColor(const QString &name);

  bool setMoleculeStyle(const StyleMapMolecule& style);

  template <class W>
  bool writeImageFormat(const QString &fileName, bool rgba = true, int scale = 1);

  void mapMolecule(vtkMolecule* pMol);

  /**
 * Write the render window view to an image file.
 * 
 * Image types supported are:
 *  BMP, JPEG, PNM, PNG, PostScript, TIFF.
 * The default parameters are used for all writers, change as needed.
 * 
 * @param fileName The file name, if no extension then PNG is assumed.
 * @param rgba Used to set the buffer type.
 * @param scale Scaling level
 * 
 * 
 */
  void writeImage(const std::string &fileName, bool rgba = true);

  template<class Writer>
  void writeImageAs(const std::string & /* fileName */, bool /* rgba */ = true);

private:
  static vtkNew<vtkNamedColors> colors_bg;
  static vtkStdString name_bg_color;

  QString name_color_bg_;
  vtkColor3d color_bg_;

  // ---
  StyleMapMolecule styleMol_;
  AMapMol mapperMol_;
  AnActor actorMol_;
  NewRender renderer_;

  AnInStyTrkCamera track_camera_;
};

#endif //!View_Molecule__h
