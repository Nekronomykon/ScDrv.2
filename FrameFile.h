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

  void InterpretFileName();

  static FrameFile *New(QWidget * /*parent*/ = Q_NULLPTR);
  static QStringList getRecentFiles() { return recent_files; }

  static QString GetFileInputContextString();
  static void BuildFileContext();
  static FileContext SetupFileInputContext(const QString &);
  static void ClearFileInputContext();
  static FileContext FormatFromPath(const QString &);

  template <class W>
  int addViewWidget(QPointer<W> &ww, const QString &title)
  {
    if (!ww)
      ww = new W(this);
    view_current_.push_back(ww);
    return this->addTab(ww, title);
  }

  void hideStructureViews()
  {
    while(this->count() > 1)
    {
      this->removeTab(1);
    }
    view_current_.resize(1);
    view_current_[0] = edit_source_; // may be excessive, but...
  }

  FileContext getFormat() const
  {
    return format_current_;
  }

  FileContext resetFormat(FileContext fmt)
  {
    if (!fmt.isCompatible(format_current_))
      std::swap(fmt, format_current_);
    return fmt;
  }

  static FileContext defaultFormat()
  {
    return format_active;
  }

  void readCurrentFormatFrom(const QString &from)
  {
    format_current_.buildFrom(*this, from);
  }
  void doClearAll();
  void doReload();

  bool readSource(const QString &);
  bool saveSource(const QString &) const;

  QString dumpSource() const
  {
    CodeEditor *pSrc = this->getEditSource();
    pSrc->dump();
    return pSrc->getDumpPath();
  }

  // Reader functionality
  template <class T>
  bool applyReaderType()
  {
    // convert to const char*
    QString str = this->dumpSource();
    if (!str.isEmpty())
    {
      vtkSmartPointer<MoleculeAcquireFile> reader(vtkSmartPointer<T>::New());
      QByteArray bytes = str.toLatin1();
      reader->ResetFileName(bytes.data());

      structure_.Initialize();
      reader->SetOutput(static_cast<vtkMolecule *>(structure_));
      reader->Update();
    }
    return bool(structure_.getMolecule()->GetNumberOfAtoms() > 0);
  }

  bool readContentXYZ();
  bool readContentWFN();
  bool readContentCUBE();
  bool readContentNone();

  CodeEditor *getEditSource() const { return edit_source_; }
  ViewMoleculeAtomic* getEditAtomic() const { return view_atomic_;}

protected:
  enum Units
  {
    Bohrs,
    Angstroms,
    Picometers
  };

private:
  static QStringList recent_files;
  static QMap<FileContext, QString> all_formats;
  static FileContext format_active;

  FileContext format_current_;

  // vtkIdTypeArray positions_;
  MolecularStructure structure_;

  //QPointer <QToolButton> extend_;
  //QPointer <QToolButton> compress_;
  QVector<QWidget *> view_current_;
  // ..chosen from:
  QPointer<EditTextSource> edit_source_;
  QPointer<QVTKMoleculeWidget> view_molecule_;
  QPointer<ViewMoleculeAtomic> view_atomic_;
};

#endif // !Frame_File_h
