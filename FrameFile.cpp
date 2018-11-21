#include "FrameFile.h"

#include <set>

#include <QFile>
#include <QSet>
#include <QMap>
#include <QList>
#include <QVector>

#include <QStringList>
#include <QMessageBox>

#include <QFile>
#include <QFileInfo>

#include <vtkStringArray.h>

#include <vtkRenderWindow.h>
#include <vtkWindowToImageFilter.h>
#include <vtkNamedColors.h>
#include <vtkImageWriter.h>

#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkBMPWriter.h>
#include <vtkPostScriptWriter.h>

#include "MoleculeAcquireFileARC.h"
#include "MoleculeAcquireFileOUT.h"
#include "MoleculeAcquireFileXYZ.h"
#include "MoleculeAcquireFileWFN.h"
#include "MoleculeAcquireFileCUBE.h"

#include "FileFormat.h"

typedef vtkSmartPointer<vtkImageWriter> ImgWrite;
typedef vtkSmartPointer<vtkPNGWriter> ImgWritePNG;
typedef vtkSmartPointer<vtkJPEGWriter> ImgWriteJPEG;
typedef vtkSmartPointer<vtkBMPWriter> ImgWriteBMP;
typedef vtkSmartPointer<vtkPostScriptWriter> ImgWritePS;

// static members
QStringList FrameFile::recent_files;

QMap<FrameFile::FileContext, QString> FrameFile::all_formats;
FrameFile::FileContext FrameFile::format_active;

// static functions
FrameFile *FrameFile::New(QWidget *parent) { return new FrameFile(parent); }

inline QStringList FrameFile::getRecentFiles() { return recent_files; }

inline QStringList &FrameFile::recentFiles() { return recent_files; }

QStringList FrameFile::GetBackgroundColorNames()
{
  vtkNew<vtkNamedColors> colors;
  vtkNew<vtkStringArray> col_names;

  colors->GetColorNames(col_names);
  QStringList names;
  size_t nNames = col_names->GetSize();
  for (size_t j = 0; j < nNames; ++j)
  {
    vtkStdString a_name(col_names->GetValue(j));
    if (a_name.empty())
      continue;
    QString sName(tr(a_name.c_str()));
    if (!sName.isEmpty())
      names << sName;
  }

  return names;
}

void FrameFile::resetRecentFiles(QStringList again_recent)
{
  std::swap(recent_files, again_recent);
}

void FrameFile::BuildFileContext()
{
  all_formats[FileContext("MOPAC run archive files", &FrameFile::acquireAsARC)] = "arc";
  all_formats[FileContext("MOPAC output files", &FrameFile::acquireAsOUT)] = "out";
  all_formats[FileContext("XMol XYZ files", &FrameFile::acquireAsXYZ)] = "xyz";
  all_formats[FileContext("Gaussian Cube files", &FrameFile::acquireAsCUBE)] = "cube";
  all_formats[FileContext("Wavefunction files", &FrameFile::acquireAsWFN)] = "wfn";
  // all_formats[FileContext("Generic text files", nullptr, &FrameFile::saveTextSource)] = "txt";
  // all_formats[FileContext("Portable Network Graphics file", nullptr, &FrameFile::writeSceneAsPNG)] = "png";
}

FrameFile::FileContext FrameFile::CastInputPathFormat(const QString &path)
{
  QFileInfo fi(path);
  QString sx = fi.suffix();
  FileContext res;

  // gathering all appropriate formats:
  QList<FileContext> all_fmts;
  auto it_fmt = all_formats.begin();
  do
  {
    if (it_fmt.key().hasBuild() && it_fmt.value() == sx) // (it_fmt.value().indexOf(sx) != -1) or whatever else similar...
      all_fmts.push_back(it_fmt.key());
  } while (++it_fmt != all_formats.end());

  if (all_fmts.size() == 1)
    res = all_fmts.front();
  // if (all_fmts.empty())  all_fmts.copy(all_formats);
  if (!res)
  {
    QMessageBox::warning(nullptr, tr("Ambiguous"), tr("More than one file format could be attributed to the following file:\n%1\nUser intervention is required").arg(path), QMessageBox::Ok | QMessageBox::Ignore);
  }
  return res;
}

QString FrameFile::keyRecentFiles() { return QStringLiteral("RecentFiles"); }
QString FrameFile::keyFile() { return QStringLiteral("File"); }
void FrameFile::storeRecentFiles(QSettings &s)
{
  writeRecentFiles(getRecentFiles(), s);
}

void FrameFile::loadRecentFiles(QSettings &s)
{
  resetRecentFiles(readRecentFiles(s));
}

QStringList FrameFile::readRecentFiles(QSettings &settings)
{
  QStringList result;
  const int count = settings.beginReadArray(keyRecentFiles());
  for (int i = 0; i < count; ++i)
  {
    settings.setArrayIndex(i);
    result.append(settings.value(keyFile()).toString());
  }
  settings.endArray();
  return result;
}

int FrameFile::writeRecentFiles(const QStringList &files, QSettings &settings)
{
  const int count = files.size();
  settings.beginWriteArray(keyRecentFiles());
  for (int i = 0; i < count; ++i)
  {
    settings.setArrayIndex(i);
    settings.setValue(keyFile(), files.at(i));
  }
  settings.endArray();
  return count;
}

void FrameFile::addToRecent(const QString &one)
{
  auto &recent_list = recentFiles();
  recent_list.removeAll(one);
  recent_list.prepend(one);
}

template <class W>
int FrameFile::addViewWidget(QPointer<W> &ww, const QString &title)
{
  if (!ww)
    ww = new W(this);
  view_current_.push_back(ww);
  return this->addTab(ww, title);
}

QString FrameFile::FileInputFilter()
{
  QString res(tr("Known file types ("));
  std::set<QString> regx;

  QString by_format;
  auto it_fmt = all_formats.begin();
  do
  {
    //if (!it_fmt.key().hasBuild())
    //  continue;

    by_format += it_fmt.key();
    QString mask(tr("*."));
    mask += it_fmt.value();

    regx.insert(mask);

    by_format += " (";
    by_format += mask;
    by_format += ");;";
  } while (++it_fmt != all_formats.end());

  assert(!regx.empty());

  QString reg;
  for (const QString &extn : regx)
  {
    reg += extn;
    reg += " ";
  }
  res += reg.trimmed();
  res += ");;";

  res += by_format;

  // If format is not uniquely detected, treat is as plain text
  res += tr("All files (*.*)");
  return res;
}

FrameFile::FileContext FrameFile::SetupFileInputContext(const QString &key)
{
  auto it_fmt = all_formats.begin();
  do
  {
    if (key.startsWith(it_fmt.key()))
    {
      format_active = it_fmt.key();
      return format_active;
    }
  } while (++it_fmt != all_formats.end());

  return FileContext();
}

void FrameFile::ClearFileInputContext()
{
  format_active = FileContext();
}

// this-driven functions
FrameFile::FrameFile(QWidget *parent)
  : QTabWidget(parent), format_current_(format_active), bonds_build_(BuildBonds::New())
  //, extend_(new QToolButton(this))
  //, compress_(new QToolButton(this))
{
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->setTabPosition(QTabWidget::South);
  this->setTabShape(QTabWidget::Rounded);
  this->tabBar()->setAutoHide(true);

  this->addViewWidget(edit_source_, tr("Source"));

  this->doClearAll();
}

FrameFile::FileContext FrameFile::resetFormat(FileContext fmt)
{
  if (!fmt.isCompatible(format_current_))
    std::swap(fmt, format_current_);
  return fmt;
}

bool FrameFile::readCurrentFormatFrom(const QString &from)
{
  return format_current_.buildFrom(*this, from);
}

bool FrameFile::interpretNone()
{
  edit_source_->setReadOnly(false);
  return true;
}

template <class T>
bool FrameFile::acquireUsing()
{
  // convert to const char*
  TypeFileName str = this->dumpSource();
  if (!str.isEmpty())
  {
    vtkSmartPointer<T> reader(vtkSmartPointer<T>::New());
    reader->SetOutput(structure_.Initialize());
    QByteArray bytes = str.toLatin1();
    reader->ResetFileName(bytes.data());

    reader->Update();
    structure_.UpdateBonds();
    this->ReadAdditionalInformation(reader.Get());
  }
  return bool(this->getMolecule()->GetNumberOfAtoms() > 0);
}

bool FrameFile::acquireAsARC() { return this->acquireUsing<MoleculeAcquireFileARC>(); }
bool FrameFile::acquireAsOUT() { return this->acquireUsing<MoleculeAcquireFileOUT>(); }
bool FrameFile::acquireAsXYZ() { return this->acquireUsing<MoleculeAcquireFileXYZ>(); }
bool FrameFile::acquireAsWFN() { return this->acquireUsing<MoleculeAcquireFileWFN>(); }
bool FrameFile::acquireAsCUBE() { return this->acquireUsing<MoleculeAcquireFileCUBE>(); }

// data facets
vtkMolecule *FrameFile::getMolecule() const
{
  return structure_.getMolecule();
}

// data views
EditTextSource *FrameFile::getEditSource() const
{
  return edit_source_;
}
EditTextSource *FrameFile::setEditSource()
{
  auto *pOne = this->getEditSource();
  if (pOne)
    this->setCurrentWidget(pOne);
  return pOne;
}

QVTKMoleculeWidget *FrameFile::getViewStructure() const
{
  return view_current_.contains(view_molecule_) ? view_molecule_ : nullptr;
}

QVTKMoleculeWidget *FrameFile::setViewStructure()
{
  auto *pOne = this->getViewStructure();
  if (pOne)
    this->setCurrentWidget(pOne);
  return pOne;
}

ViewMoleculeAtomic *FrameFile::getEditAtomic() const
{
  return view_atomic_;
}

ViewMoleculeAtomic *FrameFile::setEditAtomic()
{
  auto *pOne = this->getEditAtomic();
  if (pOne)
    this->setCurrentWidget(pOne);
  return pOne;
}

void FrameFile::InterpretFileName()
{
  this->setWindowTitle(this->GetFileName() + tr("[*]"));
}

void FrameFile::doClearAll()
{
  structure_.Initialize();
  this->hideStructureViews();
  this->resetFormat();
  edit_source_->setPlainText(tr(""));
  edit_source_->setReadOnly(false);
}

void FrameFile::hideStructureViews()
{
  this->setCurrentWidget(edit_source_);
  while (this->count() > 1)
  {
    this->removeTab(1);
  }
  view_current_.resize(1);
  view_current_[0] = edit_source_; // may be excessive, but...
}

void FrameFile::showStructureViews()
{
  this->addViewWidget(view_molecule_, tr("Structure"));
  view_molecule_->ShowMolecule(this->getMolecule());
  this->addViewWidget(view_atomic_, tr("Atoms"));
  view_atomic_->GetViewModel()->resetMolecule(this->getMolecule());
  this->addViewWidget(view_bonds_, tr("Bonds"));
  view_bonds_->GetViewModel()->resetMolecule(this->getMolecule());
}

FrameFile::FileContext FrameFile::defaultFormat() { return format_active; }

FrameFile::FileContext FrameFile::getFormat() const { return format_current_; }

void FrameFile::doReload()
{
  if (this->HasFileName())
    this->readCurrentFormatFrom(this->GetFileName());
}

bool FrameFile::readTextSource(const TypeFileName &from)
{
  QFile file(from);

  if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
    return false;

  edit_source_->load(&file);
  edit_source_->setReadOnly(false);
  return true;
}

bool FrameFile::saveTextSource(const TypeFileName &path_to) const
{
  edit_source_->dump();
  if (QFile::exists(path_to))
    QFile::remove(path_to);
  return QFile::copy(edit_source_->getDumpPath(), path_to);
}

FrameFile::TypeFileName FrameFile::dumpSource() const
{
  EditTextSource *pSrc = this->getEditSource();
  pSrc->dump();
  return pSrc->getDumpPath();
}

// image writer functions
bool FrameFile::writeSceneAsPNG(const TypeFileName &save_path)
{
  FrameFile::ViewMolecule *pMolView = this->setViewStructure();
  assert(pMolView);
  assert(pMolView == view_molecule_);

  if (pMolView != view_molecule_)
    return false;

  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".png"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  // Here comes saving...
  // TODO: Rethink saving and format casting here...

  ImgWritePNG write_image(ImgWritePNG::New());
  write_image->SetCompressionLevel(9);
  {
    vtkNew<vtkWindowToImageFilter> filter;
    filter->SetInput(pMolView->GetRenderWindow());
    write_image->SetInputConnection(filter->GetOutputPort());
  }
  write_image->SetFileName(FileNameRoot::getPtrFrom(save_file));
  write_image->Write();

  return true;
}

bool FrameFile::writeSceneAsJPEG(const TypeFileName &save_path)
{
  FrameFile::ViewMolecule *pMolView = this->setViewStructure();
  assert(pMolView);
  assert(pMolView == view_molecule_);

  if (pMolView != view_molecule_)
    return false;

  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".jpg"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  // Here comes saving...
  // TODO: Rethink saving and format casting here...

  ImgWriteJPEG write_image(ImgWriteJPEG::New());
  write_image->ProgressiveOn();
  write_image->SetQuality(75);
  {
    vtkNew<vtkWindowToImageFilter> filter;
    filter->SetInput(pMolView->GetRenderWindow());
    write_image->SetInputConnection(filter->GetOutputPort());
  }
  write_image->SetFileName(FileNameRoot::getPtrFrom(save_file));
  write_image->Write();

  return true;
}

bool FrameFile::writeSceneAsBitmap(const TypeFileName &save_path)
{
  FrameFile::ViewMolecule *pMolView = this->setViewStructure();
  assert(pMolView);
  assert(pMolView == view_molecule_);

  if (pMolView != view_molecule_)
    return false;

  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".bmp"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  // Here comes saving...
  // TODO: Rethink saving and format casting here...

  ImgWriteBMP write_image(ImgWriteBMP::New());
  {
    vtkNew<vtkWindowToImageFilter> filter;
    filter->SetInput(pMolView->GetRenderWindow());
    write_image->SetInputConnection(filter->GetOutputPort());
  }
  write_image->SetFileName(FileNameRoot::getPtrFrom(save_file));
  write_image->Write();

  return true;
}

bool FrameFile::writeSceneAsPostScript(const TypeFileName &save_path)
{
  FrameFile::ViewMolecule *pMolView = this->setViewStructure();
  assert(pMolView);
  assert(pMolView == view_molecule_);

  if (pMolView != view_molecule_)
    return false;

  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".eps"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  // Here comes saving...
  // TODO: Rethink saving and format casting here...

  ImgWritePS write_image(ImgWritePS::New());
  {
    vtkNew<vtkWindowToImageFilter> filter;
    filter->SetInput(pMolView->GetRenderWindow());
    write_image->SetInputConnection(filter->GetOutputPort());
  }
  write_image->SetFileName(FileNameRoot::getPtrFrom(save_file));
  write_image->Write();

  return true;
}
