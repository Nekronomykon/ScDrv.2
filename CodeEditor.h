#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPointer>

#include <QResizeEvent>
#include <QPaintEvent>
#include <QPlainTextEdit>
#include <QTemporaryFile>
#include <QIODevice>

class LineNumberArea;

//![codeeditordefinition]

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = 0);
    ~CodeEditor () override;

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void load(QIODevice* /*pIO*/);
    void save(QIODevice* /*pIO*/);

    void dump();

    QString getDumpPath() const;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QPointer<LineNumberArea> lineNumberArea;

    QTemporaryFile file_dump_;
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea
        : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

//![extraarea]

#endif
