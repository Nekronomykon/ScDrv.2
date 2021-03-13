#ifndef Code_Editor_h
#define Code_Editor_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>

#include <QResizeEvent>
#include <QPaintEvent>
#include <QPlainTextEdit>
#include <QIODevice>

class SideBarDecorator;

//![codeeditordefinition]

class EditCode : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit EditCode(QWidget* /*parent*/ = nullptr);
    ~EditCode () override;

    void SideBarDecoratorPaintEvent(QPaintEvent *);
    int SideBarWidth();

    void load(QIODevice* /*pIO*/);
    void save(QIODevice* /*pIO*/);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateSideBarWidth(int /*newBlockCount*/);
    void highlightCurrentLine();
    void updateSideBar(const QRect &, int);

private:
    QPointer<SideBarDecorator> side_bar_;
};

#endif // !Code_Editor_h
