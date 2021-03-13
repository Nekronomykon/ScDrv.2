#ifndef View_FileContent_h
#define View_FileContent_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QString>
#include <QListWidget>

class ViewFileContent
: public QListWidget
{
    Q_OBJECT
    public:
    typedef QListWidget _Base;
    //
    ViewFileContent(QWidget* /*parent*/ = Q_NULLPTR);
};

#endif // !View_FileContent_h
