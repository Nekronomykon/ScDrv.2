#ifndef __Frame_File_h__
#define __Frame_File_h__

#include <QPointer>
#include <QString>
#include <QStringList>
#include <QWidget>

#include <QTabWidget>

#include <QToolButton>
#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkMolecule.h>

#include "CodeEditor.h"
#include "QVTKMoleculeWidget.h"

#include "FileInputContext.h"
#include "ImplFileName.h"

class FrameFile
  : public QTabWidget
  , public ImplFileName<FrameFile,QString>
{
	Q_OBJECT
public:
	FrameFile(QWidget * /*parent*/ = Q_NULLPTR);
	~FrameFile() override;

  typedef FileInputContext<FrameFile> InputContext;

	static FrameFile *New(QWidget * /*parent*/ = Q_NULLPTR);
	static QStringList getRecentFiles() { return recent_files; }

  static QString GetFileInputContextString();

  static void SetupFileInputContext(const QString&);
  static void ClearFileInputContext();

private:
	static QStringList recent_files;
  
  InputContext format_current_;

	vtkNew<vtkMolecule> a_molecule_;

	//QPointer <QToolButton> extend_;
	//QPointer <QToolButton> compress_;

	QPointer<QVTKMoleculeWidget> view_molecule_;
	QPointer<CodeEditor> edit_source_;
};

#endif // !__Frame_File_h__
