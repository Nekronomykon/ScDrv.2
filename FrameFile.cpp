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
#include <vtkStdString.h>

#include <vtkRenderWindow.h>
#include <vtkWindowToImageFilter.h>
#include <vtkNamedColors.h>
#include <vtkImageWriter.h>

#include <vtkBMPWriter.h>
#include <vtkPostScriptWriter.h>

#include "MoleculeAcquireFileARC.h"
#include "MoleculeAcquireFileOUT.h"
#include "MoleculeAcquireFileXYZ.h"
#include "MoleculeAcquireFileWFN.h"
#include "MoleculeAcquireFileWFX.h"
#include "MoleculeAcquireFileCUBE.h"
#include "MoleculeAcquireFileMGP.h"
#include "MoleculeAcquireFileSUM.h"
#include "MoleculeAcquireFileEXTOUT.h"

#include "FileFormat.h"

#include "MapperCriticalPoints.h"

typedef vtkSmartPointer<vtkImageWriter> ImgWrite;
typedef vtkSmartPointer<vtkPNGWriter> ImgWritePNG;
typedef vtkSmartPointer<vtkJPEGWriter> ImgWriteJPEG;
typedef vtkSmartPointer<vtkBMPWriter> ImgWriteBMP;
typedef vtkSmartPointer<vtkPostScriptWriter> ImgWritePS;

// static members
QStringList FrameFile::recent_files;

QMap<FrameFile::FileContext, QString> FrameFile::all_formats;
FrameFile::FileContext FrameFile::format_active;
vtkStdString FrameFile::NameDefaultBgColor("antique_white");

// static functions
FrameFile *FrameFile::New(QWidget *parent) { return new FrameFile(parent); }

inline QStringList FrameFile::getRecentFiles() { return recent_files; }

inline QStringList &FrameFile::recentFiles() { return recent_files; }

QString FrameFile::keyRecentFiles() { return QStringLiteral("RecentFiles"); }
QString FrameFile::keyFile() { return QStringLiteral("File"); }
QString FrameFile::keyDefaultBgColor() { return QStringLiteral("BackgroundColor"); }

void FrameFile::resetRecentFiles(QStringList again_recent)
{
  std::swap(recent_files, again_recent);
}

bool FrameFile::ResetBackgroundColorName(const vtkStdString &name)
{
  if (!nameBgColor_.compare(name))
    return true;

  vtkNew<vtkNamedColors> name_colors;
  if (!view_molecule_->BackgroundColorByNameAt(name, name_colors.Get() ))
    return false;
  nameBgColor_ = name;
  ResetDefaultBgColorName(name);
  return true;
}

vtkStdString FrameFile::GetBackgroundColorName() const { return nameBgColor_; }

void FrameFile::ResetDefaultBgColorName(const vtkStdString &name)
{
  vtkNew<vtkNamedColors> named_colors;
  if (named_colors->ColorExists(name))
    NameDefaultBgColor = name;
}

void FrameFile::BuildFileContext()
{
  all_formats[FileContext("MOPAC run archive files", &FrameFile::acquireAsARC)] = "arc";
  all_formats[FileContext("MOPAC output files", &FrameFile::acquireAsOUT)] = "out";
  all_formats[FileContext("XMol XYZ files", &FrameFile::acquireAsXYZ)] = "xyz";
  all_formats[FileContext("Gaussian Cube files", &FrameFile::acquireAsCUBE)] = "cube";
  all_formats[FileContext("Wavefunction files", &FrameFile::acquireAsWFN)] = "wfn";
  all_formats[FileContext("Extended wavefunction files", &FrameFile::acquireAsWFX)] = "wfx";
  all_formats[FileContext("AIMAll Molecular Graph files", &FrameFile::acquireAsMGP)] = "mgp";
  all_formats[FileContext("AIMAll atomic summae files", &FrameFile::acquireAsSUM)] = "sum";
  all_formats[FileContext("AIMAll Extreme output", &FrameFile::acquireAsExtOut)] = "extout";
  all_formats[FileContext("Portable Network Graphics file", nullptr, &FrameFile::writeSceneAsPNG)] = "png";
  all_formats[FileContext("Encapsulated PostScript file", nullptr,&FrameFile::writeSceneAsPostScript)] = "eps";
  all_formats[FileContext("Joint Photographic Experts Group file", nullptr,&FrameFile::writeSceneAsJPEG)] = "jpeg";
  all_formats[FileContext("Flat bitmap file", nullptr,&FrameFile::writeSceneAsBitmap)] = "bmp";
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

QString FrameFile::InputFilter()
{
  QString res(tr("Known file types ("));
  std::set<QString> regx;

  QString by_format;
  auto it_fmt = all_formats.cbegin();
  do
  {
    if (!it_fmt.key().hasBuild())
      continue;

    by_format += it_fmt.key();
    QString mask(tr("*."));
    mask += it_fmt.value();

    regx.insert(mask);

    by_format += " (";
    by_format += mask;
    by_format += ");;";
  } while (++it_fmt != all_formats.cend());

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

QString FrameFile::ExportFilter()
{
  QString res(tr("Known file types ("));
  std::set<QString> regx;

  QString by_format;
  auto it_fmt = all_formats.cbegin();
  do
  {
    if (!it_fmt.key().hasExport())
      continue;

    by_format += it_fmt.key();
    QString mask(tr("*."));
    mask += it_fmt.value();

    regx.insert(mask);

    by_format += " (";
    by_format += mask;
    by_format += ");;";
  } while (++it_fmt != all_formats.cend());

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

  //this->addViewWidget(edit_source_, tr("Source"));
  this->addViewWidget(view_source_, tr("Source"));
  this->showStructureViews();
  this->ResetBackgroundColorName(GetDefaultBgColorName());

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
  assert(this->getEditSource());
  this->setEditSource()->setReadOnly(false);
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
    QByteArray bytes = str.toLatin1();
    reader->ResetFileName(bytes.data());

    // NewMolecule molNew;
    // reader->SetOutput( molNew );

    MoleculeAcquireFileQTAIM *pQ = MoleculeAcquireFileQTAIM::SafeDownCast(reader.GetPointer());
    if (pQ)
    {
      pQ->SetCriticalOutput(structure_, true);
    }
    else
      reader->SetOutput(this->getMolecule()); // only atoms

    // structure_.UpdateBonds();
    // bonds_build_->RemoveAllInputs();
    // bonds_build_->SetInputData(molNew);
    // bonds_build_->SetOutput( this->getMolecule() );

    reader->Update();
    // bonds_build_->Update();

    this->ReadAdditionalInformation(reader.Get());
    this->UpdateBonds();
    view_molecule_->ShowMolecule(this->getMolecule());
  }
  return bool(this->getMolecule()->GetNumberOfAtoms() > 0);
}

void FrameFile::UpdateBonds()
{
  if (!bonds_build_)
    return;
  NewMolecule newmol;
  bonds_build_->SetOutput(newmol);
  bonds_build_->RemoveAllInputs();
  bonds_build_->SetInputData(this->getMolecule());
  bonds_build_->Update();
  this->getMolecule()->DeepCopy(newmol);
}

template <class T>
inline bool FrameFile::ExportImageWith(const QString &name)
{
  FrameFile::ViewMolecule *pMolView = this->setViewStructure();
  assert(pMolView);
  assert(pMolView == view_molecule_);

  if (pMolView != view_molecule_)
    return false;

  vtkSmartPointer<T> write_image(vtkSmartPointer<T>::New());
  this->SetupImageWriter(write_image.GetPointer());
  {
    vtkNew<vtkWindowToImageFilter> w2img;
    w2img->SetInput(pMolView->renderWindow());
    write_image->SetInputConnection(w2img->GetOutputPort());
  }
  write_image->SetFileName(FileNameRoot::getPtrFrom(name));
  write_image->Write();

  return true;
}

// data facets
vtkMolecule *FrameFile::getMolecule() const
{
  return structure_->GetMolecule();
}

// data views
EditTextSource *FrameFile::getEditSource() const
{
  return (!view_source_) ? nullptr : view_source_->getTextSource();
}
EditTextSource *FrameFile::setEditSource()
{
  auto *pOne = this->getEditSource();
  if (pOne)
    this->setCurrentWidget(view_source_);
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
  this->hideStructureViews();
  this->resetFormat();
  this->getEditSource()->setPlainText(tr(""));
  this->getEditSource()->setReadOnly(false);

  structure_->Initialize();
}

void FrameFile::hideStructureViews()
{
  this->setCurrentWidget(view_source_);
  while (this->count() > 1)
  {
    this->removeTab(1);
  }
  view_current_.resize(1);
  view_current_[0] = view_source_; // may be excessive, but...
}

void FrameFile::showStructureViews()
{
  this->addViewWidget(view_molecule_, tr("Structure"));
  view_molecule_->ShowMolecule(this->getMolecule());
  this->addViewWidget(view_atomic_, tr("Atoms"));
  view_atomic_->GetViewModel()->resetMolecule(this->getMolecule());
  this->addViewWidget(view_bonds_, tr("Bonds"));
  view_bonds_->GetViewModel()->resetMolecule(this->getMolecule());
  this->addViewWidget(view_cycle_, tr("Cycles"));
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

  auto *pSrc = this->getEditSource();
  assert(pSrc);

  pSrc->load(&file);
  this->setEditSource()->setReadOnly(false);

  return true;
}

bool FrameFile::saveTextSource(const TypeFileName &path_to) const
{
  auto *pSrc = this->getEditSource();
  assert(pSrc);

  pSrc->dump();
  if (QFile::exists(path_to))
    QFile::remove(path_to);

  return QFile::copy(pSrc->getDumpPath(), path_to);
}

FrameFile::TypeFileName FrameFile::dumpSource() const
{
  auto *pSrc = this->getEditSource();
  assert(pSrc);

  pSrc->dump();

  return pSrc->getDumpPath();
}

bool FrameFile::acquireAsARC() { return this->acquireUsing<MoleculeAcquireFileARC>(); }
bool FrameFile::acquireAsOUT() { return this->acquireUsing<MoleculeAcquireFileOUT>(); }
bool FrameFile::acquireAsXYZ() { return this->acquireUsing<MoleculeAcquireFileXYZ>(); }
bool FrameFile::acquireAsWFN() { return this->acquireUsing<MoleculeAcquireFileWFN>(); }
bool FrameFile::acquireAsWFX() { return this->acquireUsing<MoleculeAcquireFileWFX>(); }
bool FrameFile::acquireAsCUBE() { return this->acquireUsing<MoleculeAcquireFileCUBE>(); }
bool FrameFile::acquireAsMGP() { return this->acquireUsing<MoleculeAcquireFileMGP>(); }
bool FrameFile::acquireAsSUM() { return this->acquireUsing<MoleculeAcquireFileSUM>(); }
bool FrameFile::acquireAsExtOut() { return this->acquireUsing<MoleculeAcquireFileEXTOUT>(); }

// image writer functions
bool FrameFile::writeSceneAsPNG(const TypeFileName &save_path)
{
  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".png"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  return this->ExportImageWith<vtkPNGWriter>(save_file);
}

bool FrameFile::writeSceneAsJPEG(const TypeFileName &save_path)
{
  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".jpg"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  return this->ExportImageWith<vtkJPEGWriter>(save_file);
}

bool FrameFile::writeSceneAsBitmap(const TypeFileName &save_path)
{
  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".bmp"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  return this->ExportImageWith<vtkBMPWriter>(save_file);
}

bool FrameFile::writeSceneAsPostScript(const TypeFileName &save_path)
{
  // Temporary; kind of file extension mangling
  QString save_file(save_path);
  QString ext(tr(".eps"));
  if (!save_file.endsWith(ext))
    save_file += ext;

  return this->ExportImageWith<vtkPostScriptWriter>(save_file);
}
