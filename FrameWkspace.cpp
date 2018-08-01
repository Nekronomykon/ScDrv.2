#include "FrameWkspace.h"

#include <QRect>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QApplication>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QFileInfo>
#include <QSettings>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>

#include "FileInputContext.h"

// Constructor
FrameWkspace::FrameWkspace(QWidget* parent)
  : QMainWindow(parent)
  , edit_workspace_(new EditWorkspace(this))
{
  this->setupUi(this);
  //mdiArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  //mdiArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  //mdiArea_->setViewMode(QMdiArea::TabbedView);
  //mdiArea_->setTabShape(QTabWidget::Rounded);
  //mdiArea_->setDocumentMode(true);
  //mdiArea_->setTabsMovable(true);
  //mdiArea_->setTabsClosable(true);

  //// adding a new empty file window:
  //Child* pChild = Child::New(this);
  //QMdiSubWindow* pSW = mdiArea_->addSubWindow(pChild);
  //pSW->setAttribute(Qt::WA_NativeWindow, false);
  //pSW->show();


  QDockWidget *pInit = new QDockWidget(tr("Workspace"), this);
  pInit->setWidget(edit_workspace_);
  this->addDockWidget(Qt::LeftDockWidgetArea, pInit);

  // reread
  this->restoreSettings();

  // Set up action signals and slots
  connect(actionExit_, &QAction::triggered, qApp, &QApplication::closeAllWindows);
  connect(actionAboutQt_, &QAction::triggered, qApp, &QApplication::aboutQt);

}

void FrameWkspace::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type())
  {
  case QEvent::LanguageChange:
    this->retranslateUi(this);
    break;
  default:
    break;
  }
}

void FrameWkspace::closeEvent(QCloseEvent *event)
{
  this->storeSettings();
  //mdiArea_->closeAllSubWindows();
  //if (mdiArea_->currentSubWindow())
  //{
  //  event->ignore();
  //}
  //else
  //{
    event->accept();
  //}
}

//
void FrameWkspace::addPathToWorkspace(const QString &name, bool bAutoOpen)
{
  assert(!name.isEmpty());
  if (name.isEmpty())
    return;

  QFileInfo finfo(name);
  QString pathName = finfo.canonicalFilePath();

  if (finfo.isDir())
  {
    this->addDirToWorkspace(pathName, bAutoOpen);
    return;
  }

  if (finfo.isSymLink())
  {
    this->addLinkToWorkspace(pathName, bAutoOpen);
    return;
  }

  // assuming the path here to point to a regular file
  if (finfo.isFile())
  {
    this->addFileToWorkspace(pathName, bAutoOpen);
    return;
  }

  // what is this 'name' here?
}

//
//----------------------------------------------------------------------------------------
// addDirToWorkspace(path, to_recurse) : adds all files in the dir pointed by 'path'
//                                     : to the workspace, subdirs are added recursively
//                                     : if requested. It is assumed that 'path' contains
//                                     : a fully qualified (absolute) path to a dir
//                             Returns : (none)
//----------------------------------------------------------------------------------------
void FrameWkspace::addDirToWorkspace(const QString &dir, bool bRecurse)
{
  // TODO: Probably here we should enumerate all suitable files
  // in the "name" dir and at least copy only their paths to the wkspace_,
  // but it is not Ok at the moment
  edit_workspace_->listDir(dir, bRecurse);
}
FrameWkspace::Child *FrameWkspace::addLinkToWorkspace(const QString & /* path */, bool /* bOpen */)
{
  Child *pResult(nullptr);
  // TODO: how to resolve link?
  return pResult;
}
//
//----------------------------------------------------------------------------------------
// addFileToWorkspace(path, to_open): adds path to the workspace, immediately try to open
//                                  : if requested. It is assumed that 'path' contains
//                                  : a fully qualified (absolute) path to a file
//----------------------------------------------------------------------------------------
//                           Returns : pointer to a corresponding FrameFile object,
//                                   : if there is any
//----------------------------------------------------------------------------------------
FrameWkspace::Child *FrameWkspace::addFileToWorkspace(const QString &path, bool bOpen)
{
  Child *pChild = nullptr;

  bool bNew = edit_workspace_->addFilePath(path);
  if (bOpen)
  {
    //FileFrameSource toCall = bNew ?
    //  &FrameWorkspace::createFileFrame : &FrameWorkspace::provideFileFrame;

    //if ((pChild = (this->*toCall)(path)))
    //  pChild->show();
  }
  

  return pChild;
}

void FrameWkspace::restoreSettings()
{
  QSettings stored;
    const QByteArray geometry = stored.value("Geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty())
    {
      const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
      this->resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
      this->move((availableGeometry.width() - this->width()) / 2, (availableGeometry.height() - this->height()) / 2);
    }
    else
    {
      this->restoreGeometry(geometry);
    }
  }
  //
  void FrameWkspace::storeSettings()
  {
    QSettings settings;
    settings.setValue("Geometry", this->saveGeometry());
  }

  //
  void FrameWkspace::on_actionOpen__triggered()
  {
    QFileDialog::Options options = QFileDialog::DontUseNativeDialog           // portability
      | QFileDialog::ReadOnly                    // read-only is also to read
      | QFileDialog::DontUseCustomDirectoryIcons // uniformity
      ;

    QString all_context = FrameFile::GetFileInputContextString();
    QString the_context;
    QString dir_name;

    QStringList all_paths =
      // FrameFile::queryInputFiles(the_context);
      QFileDialog::getOpenFileNames(this
        , tr("Specify input files")
        , dir_name
        , all_context
        , &the_context
        , options
      );

    if (all_paths.isEmpty())
      return;

    FileInputContextSetup<FrameFile> context(the_context);

    for (const auto &one_path : all_paths)
    {
      QFileInfo fi(one_path);
      Child *pFrame = this->addFileToWorkspace(fi.canonicalFilePath()
        , true); // ...and now open
                 //  pFrame;
    }
  }
