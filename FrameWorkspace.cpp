#include "FrameWorkspace.h"

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

// Constructor
FrameWorkspace::FrameWorkspace(QWidget* parent)
  : QMainWindow(parent)
  , edit_workspace_(new ViewWorkspace)
  , view_files_(new ViewFilesystem)
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

  this->setupActions();
  this->setupToolBars();
  this->setupDockingViews();
  // reread
  this->restoreSettings();

  // Set up action signals and slots
  connect(actionExit_, &QAction::triggered, qApp, &QApplication::closeAllWindows);
  connect(actionAboutQt_, &QAction::triggered, qApp, &QApplication::aboutQt);
  connect(edit_workspace_, &ViewWorkspace::currentTextChanged,
    this, &FrameWorkspace::loadPathContentFrom);
}

FrameWorkspace::~FrameWorkspace()
{}


void FrameWorkspace::setupActions()
{
  const QIcon iconNew = QIcon::fromTheme("document-new", QIcon(":/images/New.png"));
  actionNew_->setIcon(iconNew);
  actionNew_->setShortcuts(QKeySequence::New);

  const QIcon iconOpen = QIcon::fromTheme("document-open", QIcon(":/images/Open.png"));
  actionOpen_->setIcon(iconOpen);
  actionOpen_->setShortcuts(QKeySequence::Open);

  const QIcon iconReload = QIcon::fromTheme("document-reload", QIcon(":/images/Reload.png"));
  actionReload_->setIcon(iconReload);
  actionOpen_->setShortcuts(QKeySequence::Open);

  const QIcon iconSave = QIcon::fromTheme("document-save", QIcon(":/images/Save.png"));
  actionSave_->setIcon(iconSave);
  actionSave_->setShortcuts(QKeySequence::Save);

  const QIcon iconSaveAs = QIcon::fromTheme("document-save-as", QIcon(":/images/SaveAs.png"));
  actionSaveAs_->setIcon(iconSaveAs);
  actionSaveAs_->setShortcuts(QKeySequence::SaveAs);

  const QIcon iconExit = QIcon::fromTheme("application-exit", QIcon(":/images/Exit.png"));
  actionExit_->setIcon(iconExit);
  actionExit_->setShortcuts(QKeySequence::Quit);

  const QIcon iconUndo = QIcon::fromTheme("edit-undo", QIcon(":/images/Undo.png"));
  actionUndo_->setIcon(iconUndo);
  actionUndo_->setShortcuts(QKeySequence::Undo);

  const QIcon iconRedo = QIcon::fromTheme("edit-redo", QIcon(":/images/Redo.png"));
  actionRedo_->setIcon(iconRedo);
  actionRedo_->setShortcuts(QKeySequence::Redo);

  const QIcon iconCut = QIcon::fromTheme("edit-cut", QIcon(":/images/Cut.png"));
  actionCut_->setIcon(iconCut);
  actionCut_->setShortcuts(QKeySequence::Cut);

  const QIcon iconCopy = QIcon::fromTheme("edit-copy", QIcon(":/images/Copy.png"));
  actionCopy_->setIcon(iconCopy);
  actionCopy_->setShortcuts(QKeySequence::Copy);

  const QIcon iconPaste = QIcon::fromTheme("edit-paste", QIcon(":/images/Paste.png"));
  actionPaste_->setIcon(iconPaste);
  actionPaste_->setShortcuts(QKeySequence::Paste);

  const QIcon iconClear = QIcon::fromTheme("edit-clear", QIcon(":/images/Clear.png"));
  actionClear_->setIcon(iconClear);
  actionClear_->setShortcuts(QKeySequence::Delete);

  const QIcon iconClearAll = QIcon::fromTheme("edit-clear", QIcon(":/images/ClearAll.png"));
  actionClearAll_->setIcon(iconClearAll);
  actionClearAll_->setShortcuts(QKeySequence::DeleteCompleteLine);

}

void FrameWorkspace::setupToolBars()
{
  barTools_->addAction(actionNew_);
  barTools_->addAction(actionOpen_);
  barTools_->addAction(actionSave_);


  QToolBar *editToolBar = addToolBar(tr("Edit"));
  editToolBar->addAction(actionCut_);
  editToolBar->addAction(actionCopy_);
  editToolBar->addAction(actionPaste_);
}

void FrameWorkspace::setupDockingViews()
{
  QDockWidget *pInit;
  QDockWidget* pNext;
  pInit = new QDockWidget(tr("Files"), this);
  pInit->setWidget(view_files_);
  pNext = new QDockWidget(tr("Workspace"), this);
  pNext->setWidget(edit_workspace_);
  this->addDockWidget(Qt::LeftDockWidgetArea, pInit);
  this->tabifyDockWidget(pInit, pNext);
}

FrameWorkspace::Child* FrameWorkspace::getActiveChild() const
{
  return this->viewMoleculeFile_;
}
void FrameWorkspace::changeEvent(QEvent *e)
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

void FrameWorkspace::closeEvent(QCloseEvent *event)
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
void FrameWorkspace::addPathToWorkspace(const QString &name, bool bAutoOpen)
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
void FrameWorkspace::addDirToWorkspace(const QString &dir, bool bRecurse)
{
  // TODO: Probably here we should enumerate all suitable files
  // in the "name" dir and at least copy only their paths to the wkspace_,
  // but it is not Ok at the moment
  edit_workspace_->listDir(dir, bRecurse);
}
FrameWorkspace::Child *FrameWorkspace::addLinkToWorkspace(const QString & /* path */, bool /* bOpen */)
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
FrameWorkspace::Child *FrameWorkspace::addFileToWorkspace(const QString &path, bool bOpen)
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

void FrameWorkspace::restoreSettings()
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
void FrameWorkspace::storeSettings()
{
  QSettings settings;
  settings.setValue("Geometry", this->saveGeometry());
}

//
void FrameWorkspace::on_actionOpen__triggered()
{
  QFileDialog::Options options = QFileDialog::DontUseNativeDialog           // portability
    | QFileDialog::ReadOnly                    // read-only is also to read
    | QFileDialog::DontUseCustomDirectoryIcons // uniformity
    ;

  QString all_context = FrameFile::GetFileInputContextString();
  QString fmt_name;
  QString dir_name;

  QStringList all_paths =
    // FrameFile::queryInputFiles(fmt_name);
    QFileDialog::getOpenFileNames(this
      , tr("Specify input files")
      , dir_name
      , all_context
      , &fmt_name
      , options
    );

  if (all_paths.isEmpty())
    return;

  SetupDefaultFileContext<FrameFile> context(fmt_name);

  for (const auto &one_path : all_paths)
  {
    QFileInfo fi(one_path);
    this->addFileToWorkspace(fi.canonicalFilePath());
  }
}

void FrameWorkspace::on_actionToggleLayout__triggered()
{
  QGuiApplication::setLayoutDirection( (this->layoutDirection() == Qt::LeftToRight)
    ? Qt::RightToLeft : Qt::LeftToRight);
}

void FrameWorkspace::loadPathContentFrom(const QString& file_path)
{
  this->getActiveChild()->readCurrentFormatFrom(file_path);
}
