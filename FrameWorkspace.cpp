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
#include <QSplitter>
#include <QListWidget>

#include <QFileDialog>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFontDialog>

// #include <vtkSphereSource.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkCamera.h>

#include <vtkSmartPointer.h>

// Constructor
FrameWorkspace::FrameWorkspace(QWidget *parent) : QMainWindow(parent),
                                                  edit_workspace_(new ViewWorkspace),
                                                  view_files_(new ViewFilesystem),
                                                  view_file_content_(new ViewFileContent),
                                                  progress_(new QProgressBar),
                                                  colors_back_(new ComboBoxColors),
                                                  // printer_(new QPrinter(QPrinter::HighResolution)),
                                                  level_AA_(new QComboBox)
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

  QString sColBg(this->getActiveChild()->GetBackgroundColorName().c_str());
  colors_back_->setCurrentText(sColBg);
  connect(colors_back_, &ComboBoxColors::currentTextChanged, this, &FrameWorkspace::setSceneBackground);
  connect(level_AA_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FrameWorkspace::setSceneMultisample);

  // progress_->setWidth(200);
  // this->statusBar()->insertWidget(1, progress_, 1);

  this->updateUi();
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
  FileFormat fmt = FrameFile::CastInputPathFormat(from);
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
  // const QIcon iconNew = QIcon::fromTheme("document-new", QIcon(":/images/New.png"));
  const QIcon iconNew(":/images/New.png");
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

  const QIcon iconOrtho(":/images/ProjOrtho.png");
  actionProjOrthogonal_->setIcon(iconOrtho);

  const QIcon iconPersp(":/images/ProjPersp.png");
  actionProjPerspective_->setIcon(iconPersp);

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

  QToolBar *tbSrc = this->addToolBar(tr("Source"));
  tbSrc->addAction(actionSourceEdit_);
  tbSrc->addAction(actionSourceCast_);
  tbSrc->addSeparator();

  QToolBar *tbView = this->addToolBar(tr("View"));
  tbView->addWidget(colors_back_);
  // ?? here color QLineEdit controls could also be added
  tbView->addSeparator();
  tbView->addAction(actionProjOrthogonal_);
  tbView->addAction(actionProjPerspective_);
  tbView->addSeparator();
  int nAAMax = vtkOpenGLRenderWindow::GetGlobalMaximumNumberOfMultiSamples();
  QStringList lst;
  QString sfmt("%1");
  for (int j = 0; j < nAAMax; ++j)
    lst.push_back(sfmt.arg(j));
  level_AA_->addItems(lst);
  tbView->addWidget(level_AA_);

  QToolBar *tbMol = this->addToolBar(tr("View"));
  tbMol->addAction(actionMolFast_);
  tbMol->addAction(actionMolStick_);
  tbMol->addAction(actionMolBalls_);
  tbMol->addAction(actionMolSpace_);
  tbSrc->addSeparator();
}

void FrameWorkspace::setupDockingViews()
{
  QDockWidget *pInit;
  QDockWidget *pNext;
  pInit = new QDockWidget(tr("Files"), this);
  pInit->setWidget(view_files_);
  pNext = new QDockWidget(tr("Workspace"), this);
  QSplitter *pForm = new QSplitter(Qt::Vertical);

  pForm->addWidget(edit_workspace_);
  pForm->addWidget(view_file_content_);
  pNext->setWidget(pForm);
  this->addDockWidget(Qt::LeftDockWidgetArea, pInit);
  this->tabifyDockWidget(pInit, pNext);
  pInit->show();
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

void FrameWorkspace::updateUi()
{
  Child *pActive = this->getActiveChild();
  bool bHasChild(pActive != nullptr);

  bool bHasPath(bHasChild && pActive->HasFileName());
  actionSave_->setEnabled(bHasPath && pActive->isModified());
  actionReload_->setEnabled(bHasPath && pActive->isModified());

  FrameFile::ViewMolecule *pV = !pActive ? nullptr : pActive->getViewStructure();
  bool bHasGraph(bHasChild && pV != nullptr);

  //vtkCamera*pCam = !pV ? nullptr : pV->GetActiveCamera();

  // actionProjOrthogonal_->setChecked(pCam ? pCam->GetParallelProjection() : false);
  actionProjOrthogonal_->setEnabled(bHasGraph);

  // actionProjPerspective_->setChecked(pCam ? !pCam->GetParallelProjection() : false);
  actionProjPerspective_->setEnabled(bHasGraph);

  actionMolBalls_->setChecked(bHasGraph ? pV->MoleculeIsBallsSticks() : false);
  actionMolBalls_->setEnabled(bHasGraph);

  actionMolSpace_->setChecked(bHasGraph ? pV->MoleculeIsSpaceFill() : false);
  actionMolSpace_->setEnabled(bHasGraph);

  actionMolFast_->setChecked(bHasGraph ? pV->MoleculeIsFast() : false);
  actionMolFast_->setEnabled(bHasGraph);

  actionMolStick_->setChecked(bHasGraph ? pV->MoleculeIsSticks() : false);
  actionMolStick_->setEnabled(bHasGraph);

  actionMolBonds_->setEnabled(bHasGraph);

  actionLabelAtoms_->setEnabled(bHasGraph);
  actionLabelBonds_->setEnabled(bHasGraph);

  level_AA_->setEnabled(bHasGraph);
}

FrameWorkspace::Child *FrameWorkspace::getActiveChild() const
{
  return this->file_;
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
  Child *pRes = this->getActiveChild();

  FileFormat fmt = Child::CastInputPathFormat(name);
  if (!fmt)
    return nullptr;
  else
    pRes->resetFormat(fmt);
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

  if (!fmt)
    fmt = Child::CastInputPathFormat(path);

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

// Slots

void FrameWorkspace::loadPathContentFrom(const QString &file_path)
{
  QList<QListWidgetItem *> list = edit_workspace_->findItems(file_path, Qt::MatchExactly);
  assert(list.size() == 1);
  QListWidgetItem *pItem = list.front();

  SetupDefaultFileContext<FrameFile> context(pItem->data(Qt::UserRole).toString());

  FrameFile *pFile = this->provideFileFrame(file_path);
  this->updateUi();
}

void FrameWorkspace::setSceneBackground(const QString &name_col)
{
  vtkStdString name_bytes(name_col.toLatin1().data());

  // ComboBoxColors::ResetDefaultBackgroundColorName(name_bytes);

  FrameFile *pOpen = this->getActiveChild();
  if (pOpen)
    pOpen->ResetBackgroundColorName(name_bytes);
}
void FrameWorkspace::setSceneMultisample(int idx)
{
  Child *pOpen = this->getActiveChild();
  assert(pOpen);
  auto *pMol = pOpen->getViewStructure();
  assert(pMol);
  pMol->ResetMultisample(idx);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Auto-assigned event handlers:
///////////////////////////////////////////////////////////////////////////////////////////

void FrameWorkspace::on_actionNew__triggered()
{
  Child *pOpen = this->getActiveChild();
  pOpen->doClearAll();
  pOpen->ResetFileName();
  this->updateUi();
}

void FrameWorkspace::on_actionClone__triggered()
{
  Child *pChild = this->getActiveChild();
  assert(pChild);
  /**
   * if(pChild->hasPathAttached())
   * pChild->detachPath(); pChild->setModified(true);
   **/
  this->updateUi();
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

  for (const auto &one_path : all_paths)
  {
    QFileInfo fi(one_path);
    this->addFileToWorkspace(fi.canonicalFilePath());
  }

  QFileInfo fi(all_paths.front());
  this->loadPathContentFrom(fi.canonicalFilePath());
  this->updateUi();
}

void FrameWorkspace::on_actionToggleLayout__triggered()
{
  QGuiApplication::setLayoutDirection((this->layoutDirection() == Qt::LeftToRight)
                                          ? Qt::RightToLeft
                                          : Qt::LeftToRight);
  this->updateUi();
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

  // now we should invoke the current format context to interpret:
}

//

void FrameWorkspace::on_actionProjOrthogonal__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  vtkCamera *pCam = pMolView->GetActiveCamera();
  assert(pCam);
  if (pCam)
    pCam->ParallelProjectionOn();
  pMolView->doRender();
}

void FrameWorkspace::on_actionProjPerspective__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  vtkCamera *pCam = pMolView->GetActiveCamera();
  assert(pCam);
  if (pCam)
    pCam->ParallelProjectionOff();
  pMolView->doRender();
}

void FrameWorkspace::on_actionMolFast__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->SetMoleculeFastRender();
  this->updateUi();
}
void FrameWorkspace::on_actionMolBalls__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->SetMoleculeBallsSticks();
  this->updateUi();
}
void FrameWorkspace::on_actionMolStick__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->SetMoleculeSticksOnly();
  this->updateUi();
}
void FrameWorkspace::on_actionMolSpace__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  FrameFile::ViewMolecule *pMolView = pOpen->setViewStructure();
  assert(pMolView);
  pMolView->SetMoleculeSpaceFill();
  this->updateUi();
}

void FrameWorkspace::on_actionExportScene__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  /// pMolView-> ExportToPNG();

  QString open_file = pOpen->GetFileName(); // could be empty
  QFileInfo fi(open_file);

  QFileDialog::Options opts = QFileDialog::DontUseNativeDialog | QFileDialog::DontUseCustomDirectoryIcons;
  QString str_fmt;
  QString save_file = QFileDialog::getSaveFileName(this, tr("[Image file name]"), fi.completeBaseName()
  , tr("PostScript file (*.eps);;PNG image file (*.png);;JPEG inage file (*.jpg);;Bitmap (*.bmp);;All files (*.*)") // temporarily constant
                                                   ,
                                                   &str_fmt, opts);

  if (!save_file.isEmpty())
  {
    // && pOpen->ImplementOutputFormat(FileFrame::CastOutputPathFormat(str_fmt), save_file)
    // pOpen->formattedOutput(save_file);
    // pOpen->writeSceneAsPNG(save_file); // it does work:
    if (save_file.endsWith(".png") || str_fmt.endsWith("(*.png)"))
      pOpen->writeSceneAsPNG(save_file);
    else if (save_file.endsWith(".jpg") || str_fmt.endsWith("(*.jpg)"))
      pOpen->writeSceneAsJPEG(save_file);
    else if (save_file.endsWith(".bmp") || str_fmt.endsWith("(*.bmp)"))
      pOpen->writeSceneAsBitmap(save_file);
    else if (save_file.endsWith(".eps") || str_fmt.endsWith("(*.eps)"))
      pOpen->writeSceneAsPostScript(save_file);
    else
      QMessageBox::information(this, tr("Unknown format"), tr("Show me the easy way from here to PDF, please!"),
                               QMessageBox::Close);
  }
}

void FrameWorkspace::on_actionExportCoords__triggered()
{
}

void FrameWorkspace::on_actionSetFont__triggered()
{
  FrameFile *pOpen = this->getActiveChild();
  assert(pOpen);
  QWidget *pW = pOpen->setEditSource();
  assert(pW);

  QFontDialog::FontDialogOptions settings = // QFontDialog::NoButtons |
      QFontDialog::DontUseNativeDialog | QFontDialog::ScalableFonts | QFontDialog::MonospacedFonts;

  bool ok;
  QFont font = QFontDialog::getFont(
      &ok, pW->font(), this, tr("Set text edit font"), settings);
  if (ok)
    pW->setFont(font);
}

void FrameWorkspace::on_actionPrint__triggered()
{
  QPrinter printer(QPrinter::HighResolution);
  QPrintDialog dialog(&printer, this);
  dialog.setWindowTitle(tr("Print Document"));
  // if (editor->textCursor().hasSelection())
    // dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
  if (dialog.exec() != QDialog::Accepted)
  {
    return;
  }
}