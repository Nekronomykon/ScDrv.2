#ifndef View_Structure__h
#define View_Structure__h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>

#include <QVTKOpenGLNativeWidget.h>
#include "StyleMapMolecule.h"

using namespace vtk;

#include <vtkRenderer.h>
#include <vtkMoleculeMapper.h>
#include <vtkColor.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include "ui_ViewStructure.h"

typedef vtkSmartPointer<vtkActor> Actor;
typedef vtkSmartPointer<vtkMoleculeMapper> MapMolecule;
typedef vtkSmartPointer<vtkRenderer> Renderer;

class ViewStructure
: public QWidget
, private Ui_ViewStructure
{
    Q_OBJECT

protected:
    vtkMoleculeMapper* getMoleculeMapper() const { return mapMolecule_; }

    vtkRenderer* getRenderer() const { return renderer_; }

public:
    ViewStructure(QWidget* /*parent*/ = nullptr);
    ~ViewStructure() override = default;

private slots:
    void chooseColorName(const QString &);
    //
    void readBackgroundRed(void);
    void readBackgroundGreen(void);
    void readBackgroundBlue(void);

private:
    StyleMapMolecule style_molecule_;
    QString nameColor_;
    vtkColor3d colorBg_;

    Renderer renderer_;

    Actor actorMol_;
    MapMolecule mapMolecule_;
};

#endif // !View_Structure__h
