#ifndef __Frame_File_h__
#define __Frame_File_h__

#include <QPointer>

#include <QStringList>
#include <QWidget>

#include <QTabWidget>

#include <QToolButton>
#include "CodeEditor.h"
#include "QVTKMoleculeWidget.h"

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkMolecule.h>


class FrameFile
	: public QTabWidget
{
	Q_OBJECT
public:
	FrameFile(QWidget* /*parent*/ = Q_NULLPTR);
	~FrameFile() override;

  static FrameFile* New(QWidget* /*parent*/ = Q_NULLPTR);

	static QStringList getRecentFiles() {return recent_files;}

private:
	static QStringList recent_files;

	vtkNew<vtkMolecule> a_molecule_;

	//QPointer <QToolButton> extend_;
	//QPointer <QToolButton> compress_;

	QPointer<QVTKMoleculeWidget> view_molecule_;
	QPointer<CodeEditor> edit_source_;

};

#endif // !__Frame_File_h__
