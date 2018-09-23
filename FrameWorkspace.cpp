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
FrameWorkspace::FrameWorkspace(QWidget *parent)
    : QMainWindow(parent), edit_workspace_(new ViewWorkspace), view_files_(new ViewFilesystem)
{
  this->setupUi(this);

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
{
}

void FrameWorkspace::openAllFiles(const QStringList &all)
{
  if (all.empty())
    return;
  for (QString str_one : all)
  {
    QFileInfo fi(str_one);
    this->addFileToWorkspace(fi.canonicalFilePath());
  }
  this->loadFileContents(all.front());
}

void FrameWorkspace::loadFileContents(const QString &from)
{
  // the complete full path is assumed here in `from'
  FileFormat fmt = FrameFile::castFormatFromPath(from);
  if (fmt.hasBuild())
  {
    FrameFile *pOpen = this->getActiveChild();
    pOpen->resetFormat(fmt);
    pOpen->readCurrentFormatFrom(from);
    this->addFileToWorkspace(from, fmt);
  }
}

int FrameWorkspace::hasRecentFiles()
{
  QSettings settings;
  int count = settings.beginReadArray(FrameFile::keyRecentFiles());
  settings.endArray();
  return (count >= 0) ? count : 0;
}

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

  const QIcon iconClear = QIcon::fromTheme("edit-delete", QIcon(":/images/Clear.png"));
  actionClear_->setIcon(iconClear);
  actionClear_->setShortcuts(QKeySequence::Delete);

  const QIcon iconClearAll = QIcon::fromTheme("edit-clear", QIcon(":/images/ClearAll.png"));
  actionClearAll_->setIcon(iconClearAll);
  actionClearAll_->setShortcuts(QKeySequence::DeleteCompleteLine);

  const QIcon iconSrcEdit = QIcon::fromTheme("edit-source", QIcon(":/images/SrcEdit.png"));
  actionSourceEdit_->setIcon(iconSrcEdit);

  const QIcon iconSrcCast = QIcon::fromTheme("edit-compile", QIcon(":/images/SrcCast.png"));
  actionSourceCast_->setIcon(iconSrcCast);

  const QIcon iconMolVdW(":/images/MolVDW.png");
  actionMolSpace_->setIcon(iconMolVdW);

  const QIcon iconMolBalls(":/images/MolBalls.png");
  actionMolBalls_->setIcon(iconMolBalls);

  const QIcon iconMolFast(":/images/MolFast.png");
  actionMolFast_->setIcon(iconMolFast);

  const QIcon iconMolStick(":/images/MolStick.png");
  actionMolStick_->setIcon(iconMolStick);
}

void FrameWorkspace::setupToolBars()
{
  barTools_->addAction(actionNew_);
  barTools_->addAction(actionOpen_);
  barTools_->addAction(actionSave_);

  QToolBar *editToolBar = this->addToolBar(tr("Edit"));
  editToolBar->addAction(actionUndo_);
  editToolBar->addAction(actionRedo_);
  editToolBar->addSeparator();
  editToolBar->addAction(actionCut_);
  editToolBar->addAction(actionCopy_);
  editToolBar->addAction(actionPaste_);
  editToolBar->addSeparator();
  editToolBar->addAction(actionClear_);
  editToolBar->addAction(actionClearAll_);

  QToolBar *tbMol = this->addToolBar(tr("Molecular"));
  tbMol->addAction(actionSourceEdit_);
  tbMol->addAction(actionSourceCast_);
  tbMol->addSeparator();
  tbMol->addAction(actionMolFast_);
  tbMol->addAction(actionMolStick_);
  tbMol->addAction(actionMolBalls_);
  tbMol->addAction(actionMolSpace_);
}

void FrameWorkspace::setupDockingViews()
{
  QDockWidget *pInit;
  QDockWidget *pNext;
  pInit = new QDockWidget(tr("Files"), this);
  pInit->setWidget(view_files_);
  pNext = new QDockWidget(tr("Workspace"), this);
  pNext->setWidget(edit_workspace_);
  this->addDockWidget(Qt::LeftDockWidgetArea, pInit);
  this->tabifyDockWidget(pInit, pNext);
}

void FrameWorkspace::initRecentActions()
{
  connect(menuRecent_, &QMenu::aboutToShow, this, &FrameWorkspace::updateRecentFilesMenu);

  for (int i = 0; i < MaxRecentFiles; ++i)
  {
    recentFileActs[i] = menuRecent_->addAction(QString(), this, &FrameWorkspace::openRecentFile);
    recentFileActs[i]->setVisible(false);
  }
}

void FrameWorkspace::openRecentFile()
{
  if (const QAction *action = qobject_cast<const QAction *>(sender()))
    this->loadFileContents(action->data().toString());
}

void FrameWorkspace::updateRecentFilesMenu()
{
}

void FrameWorkspace::updateUI()
{
  Child *pActive = this->getActiveChild();
  actionSave_->setEnabled(pActive && pActive->HasFileName());
  actionReload_->setEnabled(pActive && pActive->HasFileName()
                            // && pActive->isModified()
  );
}

FrameWorkspace::Child *FrameWorkspace::getActiveChild() const
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

FrameWorkspace::Child *FrameWorkspace::provideFileFrame(const QString &name)
{
  Child *pRes = nullptr;
  /*
  QMdiSubWindow* pFound = mdiArea_->findMdiWindow(name);
  if(!pFound)
  {
    pRes = Child::New(this);
    pRes->resetFormatToDefault(); ???
    pRes->readCurrentFormatFrom(name);
    pFound = mdiArea_->addSubWindow(pRes, flags ???);
  }
  else
    pRes = static_cast<Child*>(pFound->widget());
  */

  // this is for SDI
  pRes = this->getActiveChild();

  FileFormat fmt = pRes->getFormat();
  if (!fmt.isValid())
  {
    fmt = Child::defaultFormat();
    if (!fmt)
      fmt = Child::castFormatFromPath(name);
    if (!fmt)
      return nullptr;
    else
      pRes->resetFormat(fmt);
  }
  pRes->readCurrentFormatFrom(name);
  return pRes;
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
    this->addFileToWorkspace(pathName);
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
FrameWorkspace::Child *FrameWorkspace::addFileToWorkspace(const QString &path, FileFormat fmt)
{
  Child *pChild = nullptr;

  bool bNew = edit_workspace_->addFilePath(path, fmt);
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

  FrameFile::storeRecentFiles(settings);
  settings.setValue("Geometry", this->saveGeometry());
}

void FrameWorkspace::loadPathContentFrom(const QString &file_path)
{
  QList<QListWidgetItem *> list = edit_workspace_->findItems(file_path, Qt::MatchExactly);
  assert(list.size() == 1);
  QListWidgetItem *pItem = list.front();

  SetupDefaultFileContext<FrameFile> context(pItem->data(Qt::UserRole).toString());

  FrameFile *pFile = this->provideFileFrame(file_path);
}

// Auto-assigned event handlers:

void FrameWorkspace::on_actionNew__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  pOpen->doClearAll();
  pOpen->ResetFileName();
  this->updateUI();
}

void FrameWorkspace::on_actionOpen__triggered()
{
  QFileDialog::Options options = QFileDialog::DontUseNativeDialog           // portability
                                 | QFileDialog::ReadOnly                    // read-only is also to read
                                 | QFileDialog::DontUseCustomDirectoryIcons // uniformity
      ;

  QString all_context = FrameFile::FileInputFilter();
  QString fmt_name;
  QString dir_name = QDir::currentPath();

  QStringList all_paths =
      // FrameFile::queryInputFiles(fmt_name);
      QFileDialog::getOpenFileNames(this, tr("Input files"), dir_name, all_context, &fmt_name, options);

  if (all_paths.isEmpty())
    return;

  SetupDefaultFileContext<FrameFile> context(fmt_name);

  for (const auto &one_path : all_paths)
  {
    QFileInfo fi(one_path);
    this->addFileToWorkspace(fi.canonicalFilePath(), context);
  }
  // this->openFile(all_paths.front()); // ???
  QFileInfo fi(all_paths.front());
  this->loadPathContentFrom(fi.canonicalFilePath());
  this->updateUI();
}

void FrameWorkspace::on_actionToggleLayout__triggered()
{
  QGuiApplication::setLayoutDirection((this->layoutDirection() == Qt::LeftToRight)
                                          ? Qt::RightToLeft
                                          : Qt::LeftToRight);
  this->updateUI();
}

void FrameWorkspace::on_actionSourceEdit__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::EditSource *pEditSrc = pOpen->setEditSource();
  pEditSrc->setReadOnly(false);
}

void FrameWorkspace::on_actionSourceCast__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::EditSource *pEditSrc = pOpen->setEditSource();
  pEditSrc->setReadOnly(true);
  pEditSrc->dump();

  // now we should invoke the current format context to interpret 
}

void FrameWorkspace::on_actionMolFast__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->resetStyle(FrameFile::ViewMolecule::styleFast());
  this->updateUI();
}
void FrameWorkspace::on_actionMolBalls__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->resetStyle(FrameFile::ViewMolecule::styleBall());
  this->updateUI();
}
void FrameWorkspace::on_actionMolStick__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->resetStyle(FrameFile::ViewMolecule::styleBond());
  this->updateUI();
}
void FrameWorkspace::on_actionMolSpace__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->resetStyle(FrameFile::ViewMolecule::styleFill());
  this->updateUI();
}
