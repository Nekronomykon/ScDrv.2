#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QThread>

#include <QSurfaceFormat>

#include <QVTKApplication.h>

#include "FrameWorkspace.h"

int main(int argc, char *argv[])
{
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
  QVTKApplication app(argc, argv);
  // app.setAttribute(Qt::AA_NativeWindows, false);
  QCoreApplication::setApplicationName("ScrewDriver");
  QCoreApplication::setOrganizationName("Nekronomykon");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QCommandLineParser parser;
  parser.setApplicationDescription("Viewer / editor of molecular structure text files");

  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption auto_open(QStringList() << "a" << "auto-open",
    QCoreApplication::translate("main", "Edit opened files; recurse opened directories")
  );
  parser.addOption(auto_open);

  parser.addPositionalArgument("file(s)", "The file(s) to open");
  parser.process(app);

  FrameFile::BuildFileContext();

  bool bDoOpen = parser.isSet(auto_open);

  FrameWorkspace mainWin;
  for (const auto &arg : parser.positionalArguments())
    mainWin.addPathToWorkspace(arg, bDoOpen);

  mainWin.show();
  return app.exec();
}
