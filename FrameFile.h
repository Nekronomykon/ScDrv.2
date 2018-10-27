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
#include <QSettings>

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
#include "ViewMoleculeBonds.h"

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
  typedef ImplFileName<FrameFile, QString> _FileName;
  typedef _FileName::TypeFileName TypeFileName;

  explicit FrameFile(QWidget * /*parent*/ = Q_NULLPTR);
  ~FrameFile() override;

  typedef FileFormatContext<FrameFile> FileContext;
  typedef vtkSmartPointer<BondsetBuild> BuildBonds;
  //
  typedef EditTextSource EditSource;
  typedef QVTKMoleculeWidget ViewMolecule;

  // static methods:
  static FrameFile *New(QWidget * /*parent*/ = Q_NULLPTR); // cf. mechanism in VTK

  static QStringList getRecentFiles() { return recent_files; }
  static QStringList &recentFiles() { return recent_files; }
  static void resetRecentFiles(QStringList /*rclf*/ = QStringList());

  static QString FileInputFilter();
  static void BuildFileContext();
  static FileContext SetupFileInputContext(const QString &);
  static void ClearFileInputContext();
  static FileContext castFormatFromPath(const QString &);

  static inline QString keyRecentFiles() { return QStringLiteral("RecentFiles"); }
  static inline QString keyFile() { return QStringLiteral("File"); }
  static inline void storeRecentFiles(QSettings &s)
  {
    writeRecentFiles(getRecentFiles(), s);
  }

  static inline void loadRecentFiles(QSettings &s);

  static QStringList readRecentFiles(QSettings &settings);

  static int writeRecentFiles(const QStringList &files, QSettings &settings);

  static inline void addToRecent(const QString &one);

  // thiscall methods

  void InterpretFileName(); // inherited from _FileName

  template <class W>
  int addViewWidget(QPointer<W> & /*ww*/, const QString & /*title*/);
  void hideStructureViews();
  void showStructureViews();

  static FileContext defaultFormat() { return format_active; }
  FileContext getFormat() const { return format_current_; }
  FileContext resetFormat(FileContext /*fmt*/ = FileContext());

  bool readCurrentFormatFrom(const QString &from);

  void doClearAll();
  void doReload();

  bool readTextSource(const QString &);
  bool saveTextSource(const QString &) const;

  TypeFileName dumpSource() const;

  // Reader functionality
  bool interpretNone();
  // formatted for molecules:
  bool acquireAsARC();
  bool acquireAsOUT();
  bool acquireAsXYZ();
  bool acquireAsWFN();
  bool acquireAsCUBE();

  // facets
  vtkMolecule *getMolecule() const;

  // views
  EditTextSource *getEditSource() const;
  EditTextSource *setEditSource();
  QVTKMoleculeWidget *getViewStructure() const;
  QVTKMoleculeWidget *setViewStructure();
  ViewMoleculeAtomic *getEditAtomic() const;
  ViewMoleculeAtomic *setEditAtomic();

protected:
  template <class A>
  static bool acquireStructureUsing(A *pA, MolecularStructure &str)
  {
    assert(pA);
    pA->SetOutput(str.getMolecule());
    pA->Update();
    return bool(str->GetNumberOfAtoms() > 0);
  }
  template <class T>
  bool acquireUsing();

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
  QPointer<EditSource> edit_source_;
  QPointer<QVTKMoleculeWidget> view_molecule_;
  QPointer<ViewMoleculeAtomic> view_atomic_;
  QPointer<ViewMoleculeBonds> view_bonds_;
};

#endif // !Frame_File_h
