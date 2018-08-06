#include "FrameFile.h"

#include <QFile>
#include <QSet>
#include <QMap>

#include <QStringList>

#include "MoleculeAcquireFileXYZ.h"
#include "MoleculeAcquireFileWFN.h"
#include "MoleculeAcquireFileCUBE.h"

// template<>
static inline bool operator <(const FrameFileContext & f0, const FrameFileContext &f1)
{
  return (f0.FormatName() < f1.FormatName());
}

// static members
QStringList FrameFile::recent_files;

QMap<FrameFile::FileContext, QString> FrameFile::all_formats;
FrameFile::FileContext FrameFile::format_active;

// static functions
FrameFile* FrameFile::New(QWidget*parent) { return new FrameFile(parent); }

void FrameFile::BuildFileContext()
{
  all_formats[FileContext("XMol XYZ files",      &FrameFile::readContentXYZ )] =  "xyz";
  all_formats[FileContext("Gaussian Cube files", &FrameFile::readContentCUBE)] =  "cube";
  all_formats[FileContext("Wavefunction files",  &FrameFile::readContentWFN )] =  "wfn";
  all_formats[FileContext("Text files",          &FrameFile::readContentNone)] =  "txt";
}

QString FrameFile::GetFileInputContextString()
{
  QString res;
  QSet<QString> regx;

  auto it_fmt = all_formats.begin();
  do
  {
    res += it_fmt.key();
    QString mask(tr("*."));
    mask += it_fmt.value();

    regx.insert(mask);

    res += " (";
    res += mask;
    res += ");;";
  } while (++it_fmt != all_formats.end());

  if(!regx.isEmpty())
    {
      res += "Registered types (";
      QString reg;
      for(const QString&  extn: regx)
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

void FrameFile::SetupFileInputContext(const QString & key)
{
  auto it_fmt = all_formats.begin();
  do
  {
    if(key.startsWith(it_fmt.key()))
      {
        format_active = it_fmt.key();
        break;
      }
  } while (++it_fmt != all_formats.end());
}

void FrameFile::ClearFileInputContext()
{
  format_active = FileContext();
}

// this-driven functions
FrameFile::FrameFile(QWidget* parent)
  : QTabWidget(parent)
  //, extend_(new QToolButton(this))
  //, compress_(new QToolButton(this))
  , format_current_(format_active)
  , edit_source_(new EditTextSource(this))
  , view_molecule_(new QVTKMoleculeWidget(this))
{
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->setTabPosition(QTabWidget::South);
  this->setTabShape(QTabWidget::Rounded);

  //extend_->setText(tr(">>"));
  //this->setCornerWidget(extend_, Qt::BottomLeftCorner);
  //compress_->setText(tr("<<"));
  //this->setCornerWidget(compress_, Qt::BottomRightCorner);

  this->addTab(edit_source_, tr("Source"));
  this->addTab(view_molecule_, tr("Molecule"));

  a_molecule_->Initialize();
}


FrameFile::~FrameFile() {}

bool FrameFile::readContentNone()
{
  edit_source_->setReadOnly(false);
  return true;
}

bool FrameFile::readContentXYZ()
{
  return  this->applyReaderType<MoleculeAcquireFileXYZ>();
}

bool FrameFile::readContentWFN()
{
  return  this->applyReaderType<MoleculeAcquireFileWFN>();
}

bool FrameFile::readContentCUBE()
{
  return  this->applyReaderType<MoleculeAcquireFileWFN>();
}


bool FrameFile::readSource(const QString& from)
{
  QFile file(from);

  if (file.open(QIODevice::Text | QIODevice::ReadOnly))
    return false;

  edit_source_->load(&file);
  edit_source_->setReadOnly(true);
  return true;
}

void FrameFile::InterpretFileName()
{
  this->setWindowTitle(this->GetFileName() + tr("[*]"));
}
