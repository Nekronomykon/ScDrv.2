#include <QVTKOpenGLNativeWidget.h>
#include <QVTKApplication.h>

#include <QSurfaceFormat>
#include <QCoreApplication>

#include <QCommandLineParser>
#include <QStringList>

#include "FrameBrowser.h"

int main(int argc, char *argv[])
{
  QSurfaceFormat::setDefaultFormat(ViewMolecule::defaultFormat());

  // QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

  QVTKApplication app(argc, argv);

  QCoreApplication::setApplicationName("ScDrv Browser");
  QCoreApplication::setOrganizationName("Nekronomykon");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "The file(s) to open.");
  parser.process(app);
  
  const QStringList files_to_open = parser.positionalArguments();

  FrameBrowser *pFrame = nullptr;

  for(const QString& a_file: files_to_open)
  {
      FrameBrowser *pNew = FrameBrowser::provideBrowserFor(a_file);
      pNew->tile(pFrame);
      pNew->show();
  }

  if(!pFrame) pFrame = FrameBrowser::createNewBrowser();

  pFrame->show();

  return app.exec();
}
