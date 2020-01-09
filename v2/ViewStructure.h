#ifndef ViewStructure_h__
#define ViewStructure_h__

// #include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>

class ViewStructure
  : public QVTKOpenGLNativeWidget
  {
    Q_OBJECT
    public:
    ViewStructure(){}
  };
#endif // ! ViewStructure_h__
