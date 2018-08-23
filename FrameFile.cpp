#include "FrameFile.h"

#include <QFile>
#include <QSet>
#include <QMap>
#include <QList>
#include <QVector>

#include <QStringList>
#include <QMessageBox>

#include <QFile>
#include <QFileInfo>

#include "MoleculeAcquireFileXYZ.h"
#include "MoleculeAcquireFileWFN.h"
#include "MoleculeAcquireFileCUBE.h"

#include "FileFormat.h"

// static members
QStringList FrameFile::recent_files;

QMap<FrameFile::FileContext, QString> FrameFile::all_formats;
FrameFile::FileContext FrameFile::format_active;

// static functions
FrameFile *FrameFile::New(QWidget *parent) { return new FrameFile(parent); }

void FrameFile::resetRecentFiles(QStringList rclf)
{
  std::swap(recent_files, rclf);
}

void FrameFile::BuildFileContext()
{
  all_formats[FileContext("XMol XYZ files", &FrameFile::acquireAsXYZ)] = "xyz";
  all_formats[FileContext("Gaussian Cube files", &FrameFile::acquireAsCUBE)] = "cube";
  all_formats[FileContext("Wavefunction files", &FrameFile::acquireAsWFN)] = "wfn";
  all_formats[FileContext("Generic text files", nullptr, &FrameFile::saveTextSource)] = "txt";
}

FrameFile::FileContext FrameFile::FormatFromPath(const QString &path)
{
  QFileInfo fi(path);
  QString sx = fi.suffix();
  FileContext res;

  // gathering all appropriate formats:
  QList<FileContext> all_fmts;
  auto it_fmt = all_formats.begin();
  do
  {
    if (it_fmt.value() == sx) // (it_fmt.value().indexOf(sx) != -1) or whatever else similar...
      all_fmts.push_back(it_fmt.key());
  } while (++it_fmt != all_formats.end());

  if (all_fmts.size() == 1)
    res = all_fmts.front();
  // else if (all_fmts.empty())  all_fmts.copy(all_formats);
  else
  {
      QMessageBox::warning(nullptr,tr("Ambiguous names")
                           , tr("More than one file format could be held in following file:\n%1\nUser intervention is required").arg(path)
                           , QMessageBox::Ok | QMessageBox::Ignore
                           );
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
  for (int i = 0; i < count; ++i) {
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
  for (int i = 0; i < count; ++i) {
      settings.setArrayIndex(i);
      settings.setValue(keyFile(), files.at(i));
    }
  settings.endArray();
  return count;
}

void FrameFile::addToRecent(const QString &one)
{
  auto& recent_list = recentFiles();
  recent_list.removeAll(one);
  recent_list.push_front(one);
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
  QString res;
  QSet<QString> regx;

  auto it_fmt = all_formats.begin();
  do
    {
      //if (!it_fmt.key().hasBuild())
      //  continue;

    res += it_fmt.key();
    QString mask(tr("*."));
    mask += it_fmt.value();

    regx.insert(mask);

    res += " (";
    res += mask;
    res += ");;";
  } while (++it_fmt != all_formats.end());

  if (!regx.isEmpty())
  {
    res += "Known file types (";
    QString reg;
    for (const QString &extn : regx)
    {
      reg += extn;
      reg += " ";
    }
    res += reg.trimmed();
    res += ");;";
  }
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
    : QTabWidget(parent), format_current_(format_active)
    , bonds_build_(BuildBonds::New())
//, extend_(new QToolButton(this))
//, compress_(new QToolButton(this))
{
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->setTabPosition(QTabWidget::South);
  this->setTabShape(QTabWidget::Rounded);

  //extend_->setText(tr(">>"));
  //this->setCornerWidget(extend_, Qt::BottomLeftCorner);
  //compress_->setText(tr("<<"));
  //this->setCornerWidget(compress_, Qt::BottomRightCorner);

  this->addViewWidget(edit_source_, tr("Source"));
  this->doClearAll();
}

FrameFile::~FrameFile() {}

FrameFile::FileContext FrameFile::resetFormat(FileContext fmt)
{
  if (!fmt.isCompatible(format_current_))
    std::swap(fmt, format_current_);
  return fmt;
}

bool FrameFile::readCurrentFormatFrom(const QString &from)
{ return format_current_.buildFrom(*this, from); }

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
  }
  return bool(this->getMolecule()->GetNumberOfAtoms() > 0);
}

bool FrameFile::acquireAsXYZ()
{
  return this->acquireUsing<MoleculeAcquireFileXYZ>();
}

bool FrameFile::acquireAsWFN()
{
  return this->acquireUsing<MoleculeAcquireFileWFN>();
}

bool FrameFile::acquireAsCUBE()
{
  return this->acquireUsing<MoleculeAcquireFileWFN>();
}

// data facets
vtkMolecule *FrameFile::getMolecule() const
{ return structure_.getMolecule(); }

// data views
CodeEditor *FrameFile::getEditSource() const
{ return edit_source_; }

ViewMoleculeAtomic *FrameFile::getEditAtomic() const
{ return view_atomic_;}

QVTKMoleculeWidget *FrameFile::getViewStructure() const
{ return view_molecule_; }

void FrameFile::InterpretFileName()
{
  this->setWindowTitle(this->GetFileName() + tr("[*]"));
}

void FrameFile::doClearAll()
{
  this->hideStructureViews();
  edit_source_->setReadOnly(false);
  this->resetFormat();
  structure_.Initialize();
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
  view_atomic_->getViewModel()->resetMolecule(this->getMolecule());
}

void FrameFile::doReload()
{
  this->readCurrentFormatFrom(this->GetFileName());
}

bool FrameFile::readTextSource(const QString &from)
{
  QFile file(from);

  if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
    return false;

  edit_source_->load(&file);
  edit_source_->setReadOnly(false);
  return true;
}

bool FrameFile::saveTextSource(const QString &path_to) const
{
  edit_source_->dump();
  if (QFile::exists(path_to))
    QFile::remove(path_to);
  return QFile::copy(edit_source_->getDumpPath(), path_to);
}

FrameFile::TypeFileName FrameFile::dumpSource() const
{
  CodeEditor *pSrc = this->getEditSource();
  pSrc->dump();
  return pSrc->getDumpPath();
}
