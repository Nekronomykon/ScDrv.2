#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QThread>

#include <QSurfaceFormat>

#include "QVTKMoleculeWidget.h" // to specify Surface Format, as below

#include <QVTKApplication.h>
#include <vtkOpenGLRenderWindow.h>

#include "FrameWorkspace.h"

int main(int argc, char *argv[])
{
  vtkOpenGLRenderWindow::SetGlobalMaximumNumberOfMultiSamples(8);
  QSurfaceFormat::setDefaultFormat(QVTKMoleculeWidget::defaultFormat());
  
  QVTKApplication app(argc, argv);
  // app.setAttribute(Qt::AA_NativeWindows, false);
  QCoreApplication::setApplicationName("ScrewDriver");
  QCoreApplication::setOrganizationName("Nekronomykon");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QCommandLineParser parser;
  parser.setApplicationDescription("Viewer / editor of molecular structure text files");
  parser.addHelpOption();
  parser.addVersionOption();

  // adding other cmdline options above ^^^

  parser.addPositionalArgument("file(s)", "The file(s) to open");
  parser.process(app);

  FrameFile::BuildFileContext();

  FrameWorkspace mainWin;
  for (const auto &arg : parser.positionalArguments())
    mainWin.addPathToWorkspace(arg);

  mainWin.show();
  return app.exec();
}
