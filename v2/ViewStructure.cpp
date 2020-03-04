#include "ViewStructure.h"

#include <QMessageBox>
#include <QDoubleValidator>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

#include <vtkLODActor.h>
#include <vtkOpenGLRenderer.h>
// #include <vtkOpenGLMoleculeMapper.h>

typedef vtkSmartPointer<vtkOpenGLRenderer> RendererOpenGL;
typedef vtkSmartPointer<vtkLODActor> ActorLOD;
// typedef vtkSmartPointer<vtkOpenGLMoleculeMapper> MapMoleculeOpenGL;

ViewStructure::ViewStructure(QWidget* parent)
: QWidget(parent)
, renderer_(RendererOpenGL::New())
, actorMol_(ActorLOD::New())
, mapMolecule_(MapMolecule::New())
{
    this->setupUi(this);
    //QDoubleValidator* pVR = new QDoubleValidator(0.0,1.0,6);
    // pVR->setNotation(QDoubleValidator::StandardNotation);
    // editBgRed_->setValidator(pVR);
    
    connect(colors_, &ComboBoxColors::currentTextChanged
    , this, &ViewStructure::chooseColorName);
    connect(editBgRed_,&QLineEdit::returnPressed
    , this, &ViewStructure::readBackgroundRed);
    connect(editBgGreen_,&QLineEdit::returnPressed
    , this, &ViewStructure::readBackgroundGreen);
    connect(editBgBlue_,&QLineEdit::returnPressed
    , this, &ViewStructure::readBackgroundBlue);

    actorMol_->SetMapper(mapMolecule_);
    renderer_->AddActor(actorMol_);
    view_->renderWindow()->AddRenderer(renderer_);

    this->chooseColorName(tr("gainsboro"));
}

void ViewStructure::readBackgroundRed()
{
    QString strval(editBgRed_->text());

    colorBg_.SetRed(strval.toDouble());
    QString resFmt(tr("%1"));
    editBgRed_->setText( resFmt.arg( colorBg_.GetRed()   ) );

    renderer_->SetBackground(colorBg_.GetData());
    renderer_->Render();
    // view_->repaint();
}

void ViewStructure::readBackgroundGreen()
{
    QString strval(editBgGreen_->text());

    colorBg_.SetGreen(strval.toDouble());
    QString resFmt(tr("%1"));
    editBgGreen_->setText( resFmt.arg( colorBg_.GetGreen()   ) );

    renderer_->SetBackground(colorBg_.GetData());
    renderer_->Render();
    // view_->repaint();
}

void ViewStructure::readBackgroundBlue()
{
    QString strval(editBgBlue_->text());

    colorBg_.SetBlue(strval.toDouble());
    QString resFmt(tr("%1"));
    editBgBlue_->setText( resFmt.arg( colorBg_.GetBlue()   ) );

    renderer_->SetBackground(colorBg_.GetData());
    renderer_->Render();
    // view_->repaint();
}

void ViewStructure::chooseColorName(const QString &name_col)
{
    // QMessageBox::about(this,tr("Background color "), tr("Setting to:\n %1").arg(name_col)  );

    nameColor_ = name_col;

    vtkStdString keyColor(nameColor_.toLatin1().data());

    vtkNew<vtkNamedColors> named_colors;
    named_colors->GetColor(keyColor, colorBg_);

    renderer_->SetBackground(colorBg_.GetData());
    QString resFmt(tr("%1"));

    colors_->setCurrentText(nameColor_);
    editBgRed_  ->setText( resFmt.arg( colorBg_.GetRed()   ) );
    editBgGreen_->setText( resFmt.arg( colorBg_.GetGreen() ) );
    editBgBlue_ ->setText( resFmt.arg( colorBg_.GetBlue()  ) );

    renderer_->SetBackground(colorBg_.GetData());
    renderer_->Render();
}
