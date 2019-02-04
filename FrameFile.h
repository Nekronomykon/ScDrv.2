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
// #include <vtkQtTableView.h>

using namespace vtk;

#include <vtkRenderWindow.h>
#include <vtkWindowToImageFilter.h>

#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>

#include "ViewSource.h"
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
  ~FrameFile() override = default;

  typedef FileFormatContext<FrameFile> FileContext;
  typedef vtkSmartPointer<BondsetBuild> BuildBonds;
  //
  typedef EditTextSource EditSource;
  typedef QVTKMoleculeWidget ViewMolecule;

  // static methods:
  static FrameFile *New(QWidget * /*parent*/ = Q_NULLPTR); // cf. mechanism in VTK

  static QStringList GetBackgroundColorNames();

  static QStringList getRecentFiles();
  static QStringList &recentFiles();
  static void resetRecentFiles(QStringList /*rclf*/ = QStringList());

  static QString FileInputFilter();
  static void BuildFileContext();
  static FileContext SetupFileInputContext(const QString &);
  static void ClearFileInputContext();
  static FileContext CastInputPathFormat(const QString &);

  static QString keyRecentFiles();
  static QString keyFile();
  static void storeRecentFiles(QSettings &s);

  static inline void loadRecentFiles(QSettings &s);

  static QStringList readRecentFiles(QSettings &settings);

  static int writeRecentFiles(const QStringList &files, QSettings &settings);

  static inline void addToRecent(const QString &one);

  // thiscall methods

  void InterpretFileName(); // inherited from _FileName

  bool isModified() const { return isModified_; }
  void setModified(bool b = true)
  {
    isModified_ = b;
  }

  template <class W>
  int addViewWidget(QPointer<W> & /*ww*/, const QString & /*title*/);
  void hideStructureViews();
  void showStructureViews();

  static FileContext defaultFormat();
  FileContext getFormat() const;
  FileContext resetFormat(FileContext /*fmt*/ = FileContext());

  bool readCurrentFormatFrom(const QString &from);

  void doClearAll();
  void doReload();

  bool readTextSource(const TypeFileName &);
  bool saveTextSource(const TypeFileName &) const;

  TypeFileName dumpSource() const;

  template <typename Iter, typename Check>
  static QStringList GetCompatibleFormats(Iter from, Iter to, Check check)
  {
    QStringList res;
    if (from != to)
    {
      do
      {
        if (check(from.key()))
        {
          res.push_back(from.key().Name());
        }
      } while (++from != to);
    }
    return res;
  }

  // Reader functionality
  bool interpretNone();
  // formatted for molecules:
  bool acquireAsARC();
  bool acquireAsOUT();
  bool acquireAsXYZ();
  bool acquireAsWFN();
  bool acquireAsCUBE();
  bool acquireAsMGP();
  bool acquireAsSUM();
  bool acquireAsExtOut();

  // Writer functionality
  bool writeSceneAsPNG(const TypeFileName &);
  bool writeSceneAsJPEG(const TypeFileName &);
  bool writeSceneAsBitmap(const TypeFileName &);
  bool writeSceneAsPostScript(const TypeFileName &);

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

  template <class Reader>
  void ReadAdditionalInformation(Reader *) {}

  template <class Writer>
  void SetupImageWriter(Writer *) {}

  // template<>
  void SetupImageWriter(vtkPNGWriter *pPNG)
  {
    pPNG->SetCompressionLevel(9);
  }

  void SetupImageWriter(vtkJPEGWriter *pJPG)
  {
    pJPG->ProgressiveOn();
    pJPG->SetQuality(75);
  }

  template <class TImgWrite>
  bool ExportImageWith(const QString &name);

private:
  static QStringList recent_files;
  static QMap<FileContext, QString> all_formats;
  static FileContext format_active;

  bool isModified_ = false;

  FileContext format_current_;

  // vtkIdTypeArray positions_;
  MolecularStructure structure_;

  BuildBonds bonds_build_;

  QVector<QWidget *> view_current_;
  // ..chosen from:
  // QPointer<EditSource> edit_source_;
  QPointer<ViewSource> view_source_;
  QPointer<QVTKMoleculeWidget> view_molecule_ = nullptr;
  QPointer<ViewMoleculeAtomic> view_atomic_ = nullptr;
  QPointer<ViewMoleculeBonds> view_bonds_ = nullptr;
};

#endif // !Frame_File_h
