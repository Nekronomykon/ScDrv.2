#include "FrameFile.h"

QStringList FrameFile::recent_files;

FrameFile* FrameFile::New(QWidget*parent)
{
  return new FrameFile(parent);
}

FrameFile::FrameFile(QWidget* parent)
	: QTabWidget(parent)
	//, extend_(new QToolButton(this))
	//, compress_(new QToolButton(this))
	, view_molecule_(new QVTKMoleculeWidget(this))
	, edit_source_(new CodeEditor(this))
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setTabPosition(QTabWidget::South);
	this->setTabShape(QTabWidget::Rounded);

	//extend_->setText(tr(">>"));
	//this->setCornerWidget(extend_, Qt::BottomLeftCorner);
	//compress_->setText(tr("<<"));
	//this->setCornerWidget(compress_, Qt::BottomRightCorner);

  this->addTab(view_molecule_, tr("Molecule"));
  this->addTab(edit_source_, tr("Source"));
}


FrameFile::~FrameFile(){}
