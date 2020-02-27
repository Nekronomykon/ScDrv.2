#include <QtWidgets>

#include <QFileDialog>
#include <QFontDialog>

#include "FrameBrowser.h"

static inline QString recentFilesKey() { return QStringLiteral("RecentFiles"); }
static inline QString fileKey() { return QStringLiteral("File"); }
static inline QString keyGeometry() { return QStringLiteral("Geometry"); }



FrameBrowser* FrameBrowser::provideForPath(const QString& fileName, QWidget* parent)
{
    FrameBrowser *pFound = FrameBrowser::findByPath(fileName);
    if(!pFound || pFound->isWindowModified()) // to reopen if changed?
        pFound = createForPath(fileName,parent);
    return pFound;
}

FrameBrowser* FrameBrowser::createForPath(const QString& fileName, QWidget* parent)
{
    FrameBrowser *pNew = new FrameBrowser;
    pNew->attachToPath(fileName);
    // attach the path; if successful, load file content...
    pNew->tile(parent);
    return pNew;
}
// construction:
FrameBrowser::FrameBrowser(QWidget* parent)
: QMainWindow(parent)
, viewFiles_(new ViewFilesystem)
, bHasNoFile_ (true)
, hasValidPath_(false)
{
    init();
    setCurrentFile(QString());
}

bool FrameBrowser::hasValidPath() const {return hasValidPath_; }

void FrameBrowser::markPathAsValid(bool bValid) { hasValidPath_ = bValid; }


void FrameBrowser::closeEvent(QCloseEvent *event)
{
    if (this->maybeSave()) {
        this->writeSettings();
        event->accept();
    }
    else 
        event->ignore();
}

FrameBrowser* FrameBrowser::createNewFrame()
{
    FrameBrowser *other = new FrameBrowser;
    other->tile(this);
    other->show();
    return other;
}

bool FrameBrowser::attachToPath(const QString& filePath)
{
    return true;
}

void FrameBrowser::navigateToPathModel(const QModelIndex& idx)
{
    auto* pmFile = viewFiles_->getFilesView()->GetViewModel();
    QFileInfo fi = pmFile->fileInfo(idx);
    QString path (fi.canonicalFilePath());

#ifdef EXTENDED_BOX_TRACING
    QMessageBox::about(this,tr("Browse to a file"), tr("Trying to load following path:\n%1\n -- as obtained from the browser bar")
    .arg(path)
    );
#endif

    if(fi.isFile())
    this->navigateToPath(path);
    else 
    if(fi.isSymbolicLink())
    // what to do? resolve?
    ;
    else
    if(fi.isDir())
    // viewFiles_->browseDir(fi.canonicalFilePath())
    ;
}

void FrameBrowser::navigateToPath(const QString& pathfile)
{
    // if(!this->getPathBound().compare(pathfile)) // if the pathfile is exactly the path openede here already...
        // return; // skip and flee

    if (this->hasValidPath() 
    && fileStructure_->isSourceModified() 
    && !this->maybeSave() ) 
    {
        // new file navigation cancelled due to the unsaved
        // viewFiles_->showPath( this->getPathName() );
        return;
    }
    // this->doClearAll();
    this->clearContent();
    this->clearPath();
    // (re)load
    this->loadFile(pathfile);
}

void FrameBrowser::openFile(const QString &fileName)
{
    FrameBrowser *found = FrameBrowser::findByPath(fileName);
    if (found)
    {
        found->show();
        found->raise();
        found->activateWindow();
        return;
    }

    if (!this->hasValidPath() 
    && fileStructure_->getSource()->isEmpty() 
    && !fileStructure_->isSourceModified()) 
    {
        this->loadFile(fileName);
        return;
    }

    FrameBrowser *other = FrameBrowser::createForPath(fileName,this);
    if (other->bHasNoFile_) 
    {
        delete other;
        return;
    }
    other->tile(this);
    other->show();
}

bool FrameBrowser::save()
{
    return this->hasValidPath() ? this->saveFile(pathCurrent_) : this->saveAs() ;
}

bool FrameBrowser::saveAs()
{
    auto flags = QFileDialog::DontUseNativeDialog | QFileDialog::DontUseCustomDirectoryIcons;
    QString flt_save; // fileStructure_->describeSaveFormats();
    QString* flt_sel;
    QString fileName = QFileDialog::getSaveFileName(this
    , tr("Save as")
    , pathCurrent_
    , flt_save
    , flt_sel
    , flags
    );
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void FrameBrowser::documentWasModified()
{
    setWindowModified(true);
}

void FrameBrowser::updateUi()
{
    // finally, transfer
    fileStructure_->updateTabs();
}

void FrameBrowser::init()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setupUi(this);

    // Docking views

    // Central views

    // viewStructure3D_ = new ViewStructure;
    // fileStructure_->addTab(viewStructure3D_, QString("Structure"));

    // setCentralWidget(fileStructure_);

    this->setupActions();
    this->setupToolBar();
    this->setupDockingViews();
    this->createStatusBar();

    readSettings();

    connect(fileStructure_->getSource(), &QTextDocument::contentsChanged,
            this, &FrameBrowser::documentWasModified);

    this->setUnifiedTitleAndToolBarOnMac(true);

    this->updateUi();
}

void FrameBrowser::tile(const QWidget *previous)
{
    int topFrameWidth = previous->geometry().top() - previous->pos().y();
    if (!topFrameWidth || !previous)
        topFrameWidth = 40;
        const QPoint prev = !previous ? QPoint(topFrameWidth, topFrameWidth) : previous->pos();
    const QPoint pos = prev + 2 * QPoint(topFrameWidth, topFrameWidth);
    if (QApplication::desktop()->availableGeometry(this).contains(rect().bottomRight() + pos))
        this->move(pos);
}

void FrameBrowser::setupDockingViews()
{
    // viewFiles_= new ViewFilesystem;

  QDockWidget *pInit;
  // QDockWidget *pNext;
  pInit = new QDockWidget(tr("Files"), this);
  pInit->setWidget(viewFiles_);
  // pNext = new QDockWidget(tr("Workspace"), this);
  this->addDockWidget(Qt::LeftDockWidgetArea, pInit);
  // this->tabifyDockWidget(pInit,pNext);

    connect(viewFiles_->getFilesView(), &BrowseFiles::clicked
    , this, &FrameBrowser::navigateToPathModel); 
}

void FrameBrowser::setupToolBar()
{
    QToolBar *fileToolBar = this->barTools_;
    fileToolBar->addAction(actionNew_);
    fileToolBar->addAction(actionOpen_);
    fileToolBar->addAction(actionSave_);
    fileToolBar->addSeparator();
    fileToolBar->addAction(actionAbout_);
    fileToolBar->addAction(actionAboutQt_);

    QToolBar *editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(actionUndo_);
    editToolBar->addAction(actionRedo_);
    editToolBar->addSeparator();
    editToolBar->addAction(actionCut_);
    editToolBar->addAction(actionCopy_);
    editToolBar->addAction(actionPaste_);
    editToolBar->addSeparator();
    editToolBar->addAction(actionClear_);
    editToolBar->addAction(actionClearAll_);
}

//! [implicit tr context]
void FrameBrowser::setupActions()
{
//! [implicit tr context]

    const QIcon iconNew = QIcon::fromTheme("document-new", QIcon(":/images/New.png"));
    actionNew_->setIcon(iconNew);
    actionNew_->setShortcuts(QKeySequence::New);
    actionNew_->setStatusTip(tr("Create a new file"));

    const QIcon iconOpen = QIcon::fromTheme("document-open", QIcon(":/images/Open.png"));
    actionOpen_->setIcon(iconOpen);
    actionOpen_->setShortcuts(QKeySequence::Open);
    actionOpen_->setStatusTip(tr("Open an found file"));

    const QIcon iconSave = QIcon::fromTheme("document-save", QIcon(":/images/Save.png"));
    actionSave_->setIcon(iconSave);
    actionSave_->setShortcuts(QKeySequence::Save);
    actionSave_->setStatusTip(tr("Save the document to disk"));

    const QIcon iconSaveAs = QIcon::fromTheme("document-save-as", QIcon(":/images/SaveAs.png"));
    actionSaveAs_->setIcon(iconSaveAs);
    actionSaveAs_->setShortcuts(QKeySequence::SaveAs);
    actionSaveAs_->setStatusTip(tr("Save the document under a new name"));

    // fileMenu->addSeparator();

    // QMenu *menuRecent_ = fileMenu->addMenu(tr("Recent..."));
    connect(menuRecent_, &QMenu::aboutToShow, this, &FrameBrowser::updateRecentFileActions);
    recentFileSubMenuAct = menuRecent_->menuAction();
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = menuRecent_->addAction(QString(), this, &FrameBrowser::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }
    recentFileSeparator = menuRecent_->addSeparator();
    setRecentFilesVisible(FrameBrowser::hasRecentFiles());

    const QIcon iconClose = QIcon::fromTheme("document-close", QIcon(":/images/Close.png") );
    actionClose_->setIcon(iconClose);
    actionClose_->setShortcut(tr("Ctrl+W"));
    actionClose_->setStatusTip(tr("Close this window"));
    // connect(actionClose_, &QAction::triggered, this, &QWidget::close);

    const QIcon iconExit = QIcon::fromTheme("application-exit", QIcon(":/images/Exit.png"));
    actionExit_->setIcon(iconExit);
    actionExit_->setShortcuts(QKeySequence::Quit);
    // connect(actionExit_, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    actionExit_->setStatusTip(tr("Exit the application"));

    // QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    const QIcon iconUndo = QIcon::fromTheme("edit-undo", QIcon(":/images/Undo.png"));
    actionUndo_->setIcon(iconUndo);
    actionUndo_->setShortcut(QKeySequence::Undo);

    const QIcon iconRedo = QIcon::fromTheme("edit-redo", QIcon(":/images/Redo.png"));
    actionRedo_->setIcon(iconRedo);
    actionRedo_->setShortcut(QKeySequence::Redo);

#ifndef QT_NO_CLIPBOARD
    const QIcon iconCut = QIcon::fromTheme("edit-cut", QIcon(":/images/Cut.png"));
    actionCut_->setIcon(iconCut);
    actionCut_->setShortcuts(QKeySequence::Cut);
    actionCut_->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(actionCut_, &QAction::triggered, fileStructure_->getEditSource(), &EditTextSource::cut);

    const QIcon iconCopy = QIcon::fromTheme("edit-copy", QIcon(":/images/Copy.png"));
    actionCopy_->setIcon(iconCopy);
    actionCopy_->setShortcuts(QKeySequence::Copy);
    actionCopy_->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(actionCopy_, &QAction::triggered, fileStructure_->getEditSource(), &EditTextSource::copy);

    const QIcon iconPaste = QIcon::fromTheme("edit-paste", QIcon(":/images/Paste.png"));
    actionPaste_->setIcon(iconPaste);
    actionPaste_->setShortcuts(QKeySequence::Paste);
    actionPaste_->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(actionPaste_, &QAction::triggered, fileStructure_->getEditSource(), &EditTextSource::paste);

    // menuBar()->addSeparator();
#endif // !QT_NO_CLIPBOARD

    const QIcon iconClear = QIcon::fromTheme("edit-clear",QIcon(":/imaged/Clear.png"));
    actionClear_->setIcon(iconClear);
    // actionClear_->setShortcut(QKeySequence::Clear);

    const QIcon iconClearAll = QIcon::fromTheme("edit-clear-all",QIcon(":/imaged/ClearAll.png"));
    actionClearAll_->setIcon(iconClearAll);
    // actionClear_->setShortcut(QKeySequence::ClearAll);

    const QIcon iconAbout = QIcon::fromTheme("application-about", QIcon(":/images/Help.png"));
    actionAbout_->setIcon(iconAbout);
    // connect(actionAbout_, &QAction::triggered, this, &FrameBrowser::about);
    actionAbout_->setStatusTip(tr("Show the application's About box"));

    const QIcon iconAboutQt = QIcon::fromTheme("application-about-qt", QIcon(":/images/AboutKit.png"));
    actionAboutQt_->setIcon(iconAboutQt);
    actionAboutQt_->setStatusTip(tr("Show the Qt library's About box"));

#ifndef QT_NO_CLIPBOARD
    actionCut_->setEnabled(false);
    actionCopy_->setEnabled(false);
    connect(fileStructure_->getEditSource(), &EditTextSource::copyAvailable, actionCut_, &QAction::setEnabled);
    connect(fileStructure_->getEditSource(), &EditTextSource::copyAvailable, actionCopy_, &QAction::setEnabled);
#endif // !QT_NO_CLIPBOARD
}

void FrameBrowser::createStatusBar()
{
    statusBar()->showMessage(tr("Ok now"));
}

void FrameBrowser::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value(keyGeometry(), QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void FrameBrowser::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue(keyGeometry(), saveGeometry());
}

bool FrameBrowser::maybeSave()
{
    if (!fileStructure_->isSourceModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("SDI"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void FrameBrowser::loadFile(const QString &fileName)
{
    if (fileStructure_->getEditSource()->loadPath(fileName) 
    && fileStructure_->interpretSource(fileName))
    {
    this->setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    }
}

void FrameBrowser::setRecentFilesVisible(bool visible)
{
    recentFileSubMenuAct->setVisible(visible);
    recentFileSeparator->setVisible(visible);
}

static QStringList readRecentFiles(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        result.append(settings.value(fileKey()).toString());
    }
    settings.endArray();
    return result;
}

static void writeRecentFiles(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        settings.setValue(fileKey(), files.at(i));
    }
    settings.endArray();
}

bool FrameBrowser::hasRecentFiles()
{
    QSettings settings;// ( QCoreApplication::organizationName()
    // , QCoreApplication::applicationName() );

    const int count = settings.beginReadArray(recentFilesKey());
    settings.endArray();
    return count > 0;
}

void FrameBrowser::prependToRecentFiles(const QString &fileName)
{
    QSettings settings; // ( QCoreApplication::organizationName()
    // , QCoreApplication::applicationName() );

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    this->setRecentFilesVisible(!recentFiles.isEmpty());
}

void FrameBrowser::updateRecentFileActions()
{
    QSettings settings; // (QCoreApplication::organizationName()
    // , QCoreApplication::applicationName());

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for ( ; i < count; ++i) {
        const QString fileName = FrameBrowser::strippedName(recentFiles.at(i));
        recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        recentFileActs[i]->setData(recentFiles.at(i));
        recentFileActs[i]->setVisible(true);
    }
    for ( ; i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);
}

void FrameBrowser::openRecentFile()
{
    if (const QAction *action = qobject_cast<const QAction *>(sender()))
        openFile(action->data().toString());
}

bool FrameBrowser::saveFile(const QString &fileName)
{
    bool bRes(fileStructure_->getEditSource()->savePath(fileName));
    if(bRes)
    {
    this->setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    }
    return bRes;
}

void FrameBrowser::setCurrentFile(const QString &fileName)
{
    static int sequenceNumber = 1;

    bHasNoFile_ = fileName.isEmpty();
    if (bHasNoFile_)
    {
        pathCurrent_ = tr("~/document%1.txt").arg(sequenceNumber++);
    }
    else
    {
        pathCurrent_ = QFileInfo(fileName).canonicalFilePath();
    }

    fileStructure_->getSource()->setModified(false);
    this->setWindowModified(false);

    if (!bHasNoFile_ && this->windowFilePath().compare(pathCurrent_) )
        FrameBrowser::prependToRecentFiles(pathCurrent_);

    this->setWindowFilePath(pathCurrent_);
}

QString FrameBrowser::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

FrameBrowser *FrameBrowser::findByPath(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    for (QWidget *widget: QApplication::topLevelWidgets()) {
        FrameBrowser *mainWin = qobject_cast<FrameBrowser *>(widget);
        if (mainWin && mainWin->pathCurrent_ == canonicalFilePath)
            return mainWin;
    }

    return 0;
}

void FrameBrowser::clearContent()
{
    fileStructure_->getEditSource()->clear();
    fileStructure_->getSource()->setModified(true);
}

void FrameBrowser::clearPath()
{
    pathCurrent_ = QString();
    bHasNoFile_ = true;
}

void FrameBrowser::on_actionNew__triggered()
{
    this->createNewFrame();
}

void FrameBrowser::on_actionOpen__triggered()
{
    auto flags = QFileDialog::DontUseNativeDialog 
    | QFileDialog::DontUseCustomDirectoryIcons;

    QString flt_open; // // fileStructure_->describeOpenFormats();
    QString *flt_sel = nullptr;
    
    // QMessageBox::about(this, tr("Open a file"), tr("Trying to open a file"));
    QString fileName = QFileDialog::getOpenFileName(this
    , tr("Open a file")
    , tr(".")
    , flt_open
    , flt_sel
    , flags);
    if (fileName.isEmpty()) 
        return;
        
    this->clearContent();
    this->clearPath();
    this->loadFile(fileName);
}

void FrameBrowser::on_actionReload__triggered()
{
    QString sPath = pathCurrent_;
    this->loadFile(pathCurrent_);
    this->setWindowModified(false);
}
void FrameBrowser::on_actionClone__triggered()
{
    QMessageBox::about(this, tr("Clone"), tr("Clone current content into a new unsaved file") );
    /* operation [Clone]
    * if there is a path bound to the document:
    * - the document content remains intact
    * - the file path is cleared
    * - the "modified" attribute is set
    */
   this->clearPath();
   this->setWindowModified(true);
}

void FrameBrowser::on_actionSave__triggered()
{
    QMessageBox::about(this, tr("Save"), tr("Save the content to the current path") );
    this->save(); 
}

void FrameBrowser::on_actionSaveAs__triggered() 
{ 
    QMessageBox::about(this, tr("Save as"), tr("Save the content to the new path") );
    this->saveAs(); 
}

void FrameBrowser::on_actionClose__triggered()
{
    this->close();
}

void FrameBrowser::on_actionExit__triggered()
{
    qApp->closeAllWindows();
}

void FrameBrowser::on_actionClearAll__triggered()
{
    QMessageBox::about(this, tr("Clear all"), tr("Clear all current content of the document") );
    // bool bSet = this->hasPathAttached();
    this->clearContent();
    // this->setModified(bSet);
}

void FrameBrowser::on_actionOptions__triggered()
{
    QMessageBox::about(this, tr("Options"), tr("Here should be the form / window to see and change program settings") );
}

void FrameBrowser::on_actionAbout__triggered()
{
    // FrameInfo info(this);
    // info.showModal();
    QMessageBox::about(this, tr("ScDrv Text Browser")
    , tr("The <b>ScDrv</b> software parses structure text files to find molecular structures.<br>\
It makes use of <b>SDI</b> and some other examples that demonstrates<br>\
how to write single document interface applications using Qt."));
}

void FrameBrowser::on_actionAboutQt__triggered()
{ 
    qApp->aboutQt();
}
