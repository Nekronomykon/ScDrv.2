#ifndef FrameFile_h__
#define FrameFile_h__

#include <QPointer>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

#include "TableElements.h"

#include "StyleMapMolecule.h"

using namespace vtk;

class FrameFile
: public QTabWidget
{
    Q_OBJECT
private:
    QPointer<TableElements> elements_;

    StyleMapMolecule style_mol_;

public:
    explicit FrameFile(QWidget * /*parent*/ = nullptr);
    ~FrameFile() override = default;

    TableElements* getViewElements() const {return elements_;}
};


#endif // ! FrameFile_h__