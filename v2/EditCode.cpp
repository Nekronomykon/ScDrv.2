#include "SideBarDecorator.h"

#include <QFont>
#include <QPainter>
#include <QTextStream>
#include <QTextBlock>

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <QMessageBox>

#include "ResetCursor.h"

#include "EditCode.h"

//![constructor]

EditCode::EditCode(QWidget *parent)
	: QPlainTextEdit(parent)
	, side_bar_(new SideBarDecorator(this))
{
	QFont fontSrc("Courier", 12);
	fontSrc.setStyleHint(QFont::Monospace);
	this->setFont(fontSrc);

	connect(this, &EditCode::blockCountChanged, this, &EditCode::updateSideBarWidth);
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateSideBar(QRect, int)));
	connect(this, &EditCode::cursorPositionChanged, this, &EditCode::highlightCurrentLine);

	this->updateSideBarWidth(100);
	this->highlightCurrentLine();
}

//![constructor]

//![extraAreaWidth]

int EditCode::SideBarWidth()
{
	int digits = 1;
	int num = qMax(1, this->blockCount());
	while (num >= 10) 
	{
		num /= 10;
		++digits;
	}
  
	int space = this->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits
    + 2 * fontMetrics().height() 
	+ 4 // both sides paddings
    ;

	return space;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void EditCode::updateSideBarWidth(int /* newBlockCount */)
{
	this->setViewportMargins(this->SideBarWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void EditCode::updateSideBar(const QRect &rect, int dy)
{
	if (dy)
		side_bar_->scroll(0, dy);
	else
		side_bar_->update(0, rect.y(), side_bar_->width(), rect.height());

	if (rect.contains(this->viewport()->rect()))
		this->updateSideBarWidth(0);
}

//![slotUpdateRequest]

//![resizeEvent]

void EditCode::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = this->contentsRect();
	side_bar_->setGeometry(QRect(cr.left(), cr.top(), this->SideBarWidth(), cr.height()));
}

//![resizeEvent]

//![cursorPositionChanged]

void EditCode::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) 
	{
		QTextEdit::ExtraSelection selection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = this->textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	this->setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void EditCode::SideBarDecoratorPaintEvent(QPaintEvent *event)
{
	QPainter painter(side_bar_);
	painter.fillRect(event->rect(), Qt::lightGray);

	//![extraAreaPaintEvent_0]

	//![extraAreaPaintEvent_1]
	QTextBlock block = this->firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)this->blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int)this->blockBoundingRect(block).height();
	//![extraAreaPaintEvent_1]

  int nH = this->fontMetrics().height() + 1;
	//![extraAreaPaintEvent_2]
	while (block.isValid() && top <= event->rect().bottom())
  {

		if (block.isVisible() && bottom >= event->rect().top())
    {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(nH, top, side_bar_->width() - 2 * nH, nH - 1,
				Qt::AlignRight // | Qt::AlignVCenter
        , number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}
//![extraAreaPaintEvent_2]

void EditCode::load(QIODevice* pIO)
{
	QTextStream in(pIO);
	ResetCursor rc(Qt::WaitCursor);
	this->setPlainText(in.readAll());
}

void EditCode::save(QIODevice* pIO)
{
	QTextStream out(pIO);
	ResetCursor rc(Qt::WaitCursor);
	out << this->toPlainText();
}

bool EditCode::loadPath(const QString& fileName)
{
	QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) 
	{
		QString strTitle(tr("Load file error"));
		QString strMessage(tr("Cannot open file %1:\n%2."));
       	QMessageBox::warning(this
       	, strTitle
       	, strMessage.arg(QDir::toNativeSeparators(fileName), file.errorString() ) );
	    return false;
    }
	this->load(&file);
	return true;
}

bool EditCode::savePath(const QString& fileName)
{
	QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QString strTitle(tr("Save file error"));
		QString strMessage(tr("Cannot save file %1:\n%2."));
       	QMessageBox::warning(this
       	, strTitle
       	, strMessage.arg(QDir::toNativeSeparators(fileName), file.errorString() ) );
   	    return false;
	}

	this->save(&file);
	return true;
}