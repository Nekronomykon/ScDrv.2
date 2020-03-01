#include <QVTKApplication.h>
#include <QCommandLineParser>

// #include <QSystemTrayIcon>

#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>

#include "FrameBrowser.h"

int main(int argc, char *argv[])
{
    // before initializing QApplication, set the default surface format
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    
    QVTKApplication app(argc,argv);
    QCoreApplication::setApplicationName("ScDrv Browser");
    QCoreApplication::setOrganizationName("ScrewDriver");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file(s) to open.");
    parser.process(app);

    FrameBrowser *frame = nullptr;
    foreach (const QString &filename, parser.positionalArguments()) 
    {
        FrameBrowser *frameFile = FrameBrowser::provideForPath(filename,frame);
        if(frameFile)
        {
            frameFile->tile(frame);
            frameFile->show();
            frame = frameFile;
        }
    }

    // finally, if none of valid file path is given from the command line
    if (!frame) {
        frame = new FrameBrowser;
        frame->show();
    }

    return app.exec();
}
