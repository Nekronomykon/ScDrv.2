#ifndef FrameFile_h__
#define FrameFile_h__

#include <QPointer>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

#include "TableElements.h"
#include "EditTextSource.h"

#include "StyleMapMolecule.h"

using namespace vtk;

class FrameFile
: public QTabWidget
{
    Q_OBJECT
private:
    QPointer<TableElements> elements_;
    QPointer<EditTextSource> source_;

    StyleMapMolecule style_molecule_;

public:
    explicit FrameFile(QWidget * /*parent*/ = nullptr);
    ~FrameFile() override = default;

    TableElements* getViewElements() const {return elements_;}
    EditTextSource* getEditSource() const {return source_;}
    QTextDocument* getSource() const {return !source_ ? nullptr : source_->document();}
    bool isSourceModified() const {return !source_ ? false : this->getSource()->isModified();}

    void updateTabs();
};


#endif // ! FrameFile_h__