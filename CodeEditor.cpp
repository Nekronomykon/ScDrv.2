#include "CodeEditor.h"

#include "SideBarDecorator.h"

#include <QFont>
#include <QPainter>
#include <QTextStream>
#include <QTextBlock>
#include <QFileInfo>

#include "ResetCursor.h"

//![constructor]

CodeEditor::CodeEditor(QWidget *parent)
	: QPlainTextEdit(parent)
	, side_bar_(new SideBarDecorator(this))
	, file_dump_(tr("./SqD-XXXXXX.sq-drv"))
{
	file_dump_.setAutoRemove(true);
	file_dump_.open();

	QFont fontSrc("Courier", 10);
	fontSrc.setStyleHint(QFont::Monospace);
	this->setFont(fontSrc);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateSideBarDecoratorWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateSideBarDecorator(QRect, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	this->updateSideBarDecoratorWidth(0);
	this->highlightCurrentLine();
}

CodeEditor::~CodeEditor()
{
	file_dump_.close();
}

//![constructor]

//![extraAreaWidth]

int CodeEditor::SideBarWidth()
{
	int digits = 1;
	int max = qMax(1, this->blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void CodeEditor::updateSideBarDecoratorWidth(int /* newBlockCount */)
{
	setViewportMargins(this->SideBarWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void CodeEditor::updateSideBarDecorator(const QRect &rect, int dy)
{
	if (dy)
		side_bar_->scroll(0, dy);
	else
		side_bar_->update(0, rect.y(), side_bar_->width(), rect.height());

	if (rect.contains(this->viewport()->rect()))
		this->updateSideBarDecoratorWidth(0);
}

//![slotUpdateRequest]

//![resizeEvent]

void CodeEditor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	side_bar_->setGeometry(QRect(cr.left(), cr.top(), this->SideBarWidth(), cr.height()));
}

//![resizeEvent]

//![cursorPositionChanged]

void CodeEditor::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	this->setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void CodeEditor::SideBarDecoratorPaintEvent(QPaintEvent *event)
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

	//![extraAreaPaintEvent_2]
	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, side_bar_->width(), fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}
//![extraAreaPaintEvent_2]

void CodeEditor::load(QIODevice* pIO)
{
	QTextStream in(pIO);
	ResetCursor rc(Qt::WaitCursor);
	this->setPlainText(in.readAll());
}

void CodeEditor::save(QIODevice* pIO)
{
	QTextStream out(pIO);
	ResetCursor rc(Qt::WaitCursor);
	out << this->toPlainText();
}

void CodeEditor::dump()
{
	this->save(&file_dump_);
	file_dump_.seek(0L);
}

QString CodeEditor::getDumpPath() const
{
	return QFileInfo(file_dump_.fileName()).canonicalFilePath();
}
