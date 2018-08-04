#include "FrameFile.h"

#include <QFile>

#include "MoleculeAcquireFileXYZ.h"

// static members
QStringList FrameFile::recent_files;

QMap<FrameFile::FileContext, QString> FrameFile::all_formats;

// static functions
FrameFile* FrameFile::New(QWidget*parent) { return new FrameFile(parent); }

void FrameFile::BuildFileContext()
{
  all_formats[FileContext("XMol XYZ files", &FrameFile::readContentXYZ)] = "xyz";
  all_formats[FileContext("Text files", &FrameFile::readContentNone)]    = "txt";
}

QString FrameFile::GetFileInputContextString()
{
  QString res;
  QSet<QString> regx;

  auto it_is_format = all_formats.begin();
  do
  {
    res += it_is_format.key();
    QString mask(tr("*."));
    mask += it_is_format.value();

    regx.insert(mask);

    res += " (";
    res += mask;
    res += ");;";
  } while (++it_is_format != all_formats.end());

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

FrameFile::FrameFile(QWidget* parent)
  : QTabWidget(parent)
  //, extend_(new QToolButton(this))
  //, compress_(new QToolButton(this))
  , edit_source_(new CodeEditor(this))
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
