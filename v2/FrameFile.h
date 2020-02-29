#ifndef FrameFile_h__
#define FrameFile_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

// #include "TableElements.h"
#include "EditTextSource.h"
#include "ViewStructure.h"

class FrameFile
: public QTabWidget
{
    Q_OBJECT
private:
    // QPointer<TableElements> elements_;
    QPointer<EditTextSource> source_;
    QPointer<ViewStructure> visual_;


public:
    explicit FrameFile(QWidget * /*parent*/ = nullptr);
    ~FrameFile() override = default;

    EditTextSource* getEditSource() const {return source_;}
    QTextDocument* getSource() const {return !source_ ? nullptr : source_->document();}

    bool isSourceModified() const {return !source_ ? false : this->getSource()->isModified();}

    void updateTabs();

    // building an internal data representation for the source 
    bool interpretSource(const QString& /*context << path*/); 
    // argument is used mostly to interpret the information concerinig those data format
};


#endif // ! FrameFile_h__