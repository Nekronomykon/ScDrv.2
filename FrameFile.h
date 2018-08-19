#ifndef Frame_File_h
#define Frame_File_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>

#include <QString>
#include <QStringList>
#include <QWidget>
#include <QMap>

#include <QTabWidget>
#include "ImplFileName.h"

// #include <QToolButton>

#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include <vtkIdTypeArray.h>
#include <vtkMolecule.h>

#include "EditTextSource.h"
#include "QVTKMoleculeWidget.h"
// temporary view header to implement table views of atoms / bonds in Molecule
#include <vtkQtTableView.h>
#include "ViewMoleculeAtomic.h"

#include "MoleculeAcquireFile.h"

#include "MolecularStructure.h"

#include "BondsetBuild.h"

#include "FileFormat.h"

class FrameFile;
typedef class FileFormatContext<FrameFile> FrameFileContext;

class FrameFile
    : public QTabWidget,
      public ImplFileName<FrameFile, QString>
{
  Q_OBJECT
public:
  FrameFile(QWidget * /*parent*/ = Q_NULLPTR);
  ~FrameFile() override;

  typedef FileFormatContext<FrameFile> FileContext;
  typedef vtkSmartPointer<BondsetBuild> BuildBonds;

  void InterpretFileName();

  static FrameFile *New(QWidget * /*parent*/ = Q_NULLPTR); // cf. mechanism in VTK

  static QStringList getRecentFiles() { return recent_files; }

  static QString FileInputFilter();
  static void BuildFileContext();
  static FileContext SetupFileInputContext(const QString &);
  static void ClearFileInputContext();
  static FileContext FormatFromPath(const QString &);

  template <class W>
  int addViewWidget(QPointer<W> & /*ww*/, const QString & /*title*/);
  void hideStructureViews();
  void showStructureViews();

  static FileContext defaultFormat() {return format_active;}
  FileContext getFormat() const {return format_current_; }
  FileContext resetFormat(FileContext /*fmt*/ = FileContext());

  bool readCurrentFormatFrom(const QString &from);

  void doClearAll();
  void doReload();

  bool readTextSource(const QString &);
  bool saveTextSource(const QString &) const;

  TypeFileName dumpSource() const;

  // Reader functionality
  bool interpretNone();
  bool interpretSourceXYZ();
  bool interpretSourceWFN();
  bool interpretSourceCUBE();

// facets
  vtkMolecule* getMolecule() const { return structure_.getMolecule(); }

  // views
  CodeEditor *getEditSource() const { return edit_source_; }
  ViewMoleculeAtomic* getEditAtomic() const { return view_atomic_;}
  QVTKMoleculeWidget* getViewStructure() const { return view_molecule_; }

protected:
  template <class T>  bool applyReaderType();

private:
  static QStringList recent_files;
  static QMap<FileContext, QString> all_formats;
  static FileContext format_active;

  FileContext format_current_;

  // vtkIdTypeArray positions_;
  MolecularStructure structure_;

  BuildBonds bonds_build_;

  //QPointer <QToolButton> extend_;
  //QPointer <QToolButton> compress_;
  QVector<QWidget *> view_current_;
  // ..chosen from:
  QPointer<EditTextSource> edit_source_;
  QPointer<QVTKMoleculeWidget> view_molecule_;
  QPointer<ViewMoleculeAtomic> view_atomic_;
};

#endif // !Frame_File_h
