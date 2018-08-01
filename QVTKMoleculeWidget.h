#ifndef __QVTK_MoleculeWidget_h__
#define __QVTK_MoleculeWidget_h__

#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLSimpleWidget.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkMolecule.h>
#include <vtkMoleculeMapper.h>


class QVTKMoleculeWidget
	: public QVTKOpenGLWidget
{
	Q_OBJECT
public:
	QVTKMoleculeWidget(QWidget* /*parent*/ = Q_NULLPTR);
	~QVTKMoleculeWidget() override;

  typedef vtkSmartPointer<vtkActor> Actor;
  typedef vtkSmartPointer<vtkMoleculeMapper> MolMapper;
  typedef vtkSmartPointer<vtkRenderer> Renderer;

private:
  MolMapper mol_mapper_;

};

#endif // !__QVTK_MoleculeWidget_h__
