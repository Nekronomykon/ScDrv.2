#ifndef FrameFile_h__
#define FrameFile_h__

#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class FrameFile
: public QTabWidget
{
    Q_OBJECT
private:
    /* data */
public:
    explicit FrameFile(QWidget * /*parent*/ = nullptr);
    ~FrameFile() override = default;
};


#endif // ! FrameFile_h__