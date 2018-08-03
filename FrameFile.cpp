#include "FrameFile.h"

#include <QFile>

#include "MoleculeAcquireFileXYZ.h"

// static members
QStringList FrameFile::recent_files;

QMap<QString,FrameFile::FileContext> FrameFile::all_formats;

// static functions
FrameFile* FrameFile::New(QWidget*parent) {  return new FrameFile(parent); }

void FrameFile::BuildFileContext()
{
  all_formats[tr("XMol XYtZ file")] = FrameFile::FileContext(tr("xyz"), &FrameFile::readContentXYZ);
}

QString FrameFile::GetFileInputContextString() { return tr("XYZ file (*.xyz);;All files (*.*)"); }

void FrameFile::SetupFileInputContext(const QString& context)
{
  if (context.isEmpty())
    return;
}

void FrameFile::ClearFileInputContext()
{}

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


FrameFile::~FrameFile(){}

bool FrameFile::readContentXYZ()
{
    return  this->applyReaderType<MoleculeAcquireFileXYZ>();
}

bool FrameFile::readSource(const QString& from)
{
    QFile file(from);

    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
        return false;

    edit_source_->load(&file);
    return true;
}

void FrameFile::InterpretFileName()
{
    this->setWindowTitle(this->GetFileName() + tr("[*]"));
}
