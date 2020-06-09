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
#include <vtkStdString.h>

#include "EditTextSource.h"
#include "QVTKMoleculeWidget.h"
// temporary view header to implement table views of atoms / bonds in Molecule
// #include <vtkQtTableView.h>

using namespace vtk;

#include <vtkMoleculeMapper.h>

#include <vtkRenderWindow.h>
#include <vtkWindowToImageFilter.h>

#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>

#include "ViewSource.h"
#include "ViewMoleculeAtomic.h"
#include "ViewMoleculeBonds.h"
#include "ViewCyclePucker.h"

// #include "MoleculeAcquireFile.h"
// #include "MoleculeAcquireFileQM.h"
#include "MoleculeAcquireFileQTAIM.h"

#include "MapperMolecule.h"
#include "MapperCriticalPoints.h"

#include "MolecularStructure.h"

#include "BondsetBuild.h"

#include "FileFormat.h"

class FrameFile;
typedef class FileFormatContext<FrameFile> FrameFileContext;

typedef vtkNew<CriticalPoints> NewCritPoints;

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

  static QStringList getRecentFiles();
  static QStringList &recentFiles();
  static void resetRecentFiles(QStringList /*rclf*/ = QStringList());

  static QString InputFilter();
  static QString ExportFilter();
  static void BuildFileContext();
  static FileContext SetupFileInputContext(const QString &);
  static void ClearFileInputContext();
  static FileContext CastInputPathFormat(const QString &);

  static QString keyRecentFiles();
  static QString keyFile();
  static QString keyDefaultBgColor();

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

  bool hasValidPath() const;

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

  bool ResetBackgroundColorName(const vtkStdString &name);
  vtkStdString GetBackgroundColorName() const;

  static vtkStdString GetDefaultBgColorName() { return NameDefaultBgColor; }
  static void ResetDefaultBgColorName(const vtkStdString &name);

  // Reader functionality
  bool interpretNone();
  // formatted for molecules:
  bool acquireAsARC();
  bool acquireAsOUT();
  bool acquireAsXYZ();
  bool acquireAsWFN();
  bool acquireAsWFX();
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
  void UpdateBonds();

  // faceting all views:
  EditTextSource *getEditSource() const;
  EditTextSource *setEditSource();
  QVTKMoleculeWidget *getViewStructure() const;
  QVTKMoleculeWidget *setViewStructure();
  ViewMoleculeAtomic *getEditAtomic() const;
  ViewMoleculeAtomic *setEditAtomic();

protected:
  template <class>
  bool acquireUsing();
  template <class Reader>
  void ReadAdditionalInformation(Reader *) {}
  template <class Writer>
  void SetupImageWriter(Writer *) {}

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

  NewCritPoints structure_;
  vtkNew<vtkStringArray> labelAtoms_;
  vtkNew<vtkStringArray> labelBonds_;

  BuildBonds bonds_build_;

  QVector<QWidget *> view_current_;
  // ..chosen from:
  // QPointer<EditSource> edit_source_;
  QPointer<ViewSource> view_source_;
  QPointer<QVTKMoleculeWidget> view_molecule_ = nullptr;
  static vtkStdString NameDefaultBgColor;
  vtkStdString nameBgColor_;

  QPointer<ViewMoleculeAtomic> view_atomic_ = nullptr;
  QPointer<ViewMoleculeBonds> view_bonds_ = nullptr;
  QPointer<ViewCyclePucker> view_cycle_ = nullptr;
};

#endif // !Frame_File_h
