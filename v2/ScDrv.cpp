#include <QVTKApplication.h>
#include <QCommandLineParser>

#include <QSystemTrayIcon>

#include "FrameBrowser.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(ViewStructure::defaultFormat());
    
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
        FrameBrowser *frameFile = new FrameBrowser(nullptr);
        frameFile->tile(frame);
        frameFile->show();
        frame = frameFile;
    }

    if (!frame) {
        frame = new FrameBrowser;
        frame->show();
    }

    return app.exec();
}
