#ifndef __Code_Editor_h__
#define __Code_Editor_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>

#include <QResizeEvent>
#include <QPaintEvent>
#include <QPlainTextEdit>
#include <QTemporaryFile>
#include <QIODevice>

class SideBarDecorator;

//![codeeditordefinition]

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget* /*parent*/ = 0);
    ~CodeEditor () override;

    void SideBarDecoratorPaintEvent(QPaintEvent *event);
    int SideBarWidth();

    void load(QIODevice* /*pIO*/);
    void save(QIODevice* /*pIO*/);

    void dump();

    QString getDumpPath() const;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateSideBarWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateSideBar(const QRect &, int);

private:
    QPointer<SideBarDecorator> side_bar_;

    QTemporaryFile file_dump_;
};

#endif // !__Code_Editor_h__
