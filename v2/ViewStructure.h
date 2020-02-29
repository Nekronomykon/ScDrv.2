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


#include "ui_ViewStructure.h"

class ViewStructure
: public QWidget
, private Ui_ViewStructure
{
    Q_OBJECT
public:
    ViewStructure(QWidget* /*parent*/ = nullptr);
    ~ViewStructure() override = default;
private:
    StyleMapMolecule style_molecule_;
};

#endif // !View_Structure__h
