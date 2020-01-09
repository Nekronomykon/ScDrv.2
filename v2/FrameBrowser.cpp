#include <QtWidgets>

#include <QFileDialog>
#include <QFontDialog>

#include "FrameBrowser.h"

static inline QString recentFilesKey() { return QStringLiteral("RecentFiles"); }
static inline QString fileKey() { return QStringLiteral("File"); }
static inline QString keyGeometry() { return QStringLiteral("Geometry"); }

FrameBrowser::FrameBrowser(QWidget* parent)
: QMainWindow(parent)
{
    init();
    setCurrentFile(QString());
}

FrameBrowser::FrameBrowser(QWidget *parent, const QString &fileName)
: QMainWindow(parent)
{
    init();

    if(fileName.isEmpty())
        this->setCurrentFile(fileName);
    else  
        this->loadFile(fileName);
}

void FrameBrowser::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

FrameBrowser* FrameBrowser::newFile()
{
    FrameBrowser *other = new FrameBrowser;
    other->tile(this);
    other->show();
    return other;
}


void FrameBrowser::openFile(const QString &fileName)
{
    FrameBrowser *existing = findMainWindow(fileName);
    if (existing) {
        existing->show();
        existing->raise();
        existing->activateWindow();
        return;
    }

    if (bHasNoFile_ && editFileContent_->document()->isEmpty() && !isWindowModified()) {
        loadFile(fileName);
        return;
    }

    FrameBrowser *other = new FrameBrowser(nullptr,fileName);
    if (other->bHasNoFile_) {
        delete other;
        return;
    }
    other->tile(this);
    other->show();
}

bool FrameBrowser::save()
{
    return bHasNoFile_ ? saveAs() : saveFile(curFile);
}

bool FrameBrowser::saveAs()
{
    auto flags = QFileDialog::DontUseNativeDialog | QFileDialog::DontUseCustomDirectoryIcons;
    QString flt_save; // tabViews_->describeSaveFormats();
    QString* flt_sel;
    QString fileName = QFileDialog::getSaveFileName(this
    , tr("Save as")
    , curFile
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

}

void FrameBrowser::init()
{
    this->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    bHasNoFile_ = true;

    // Docking views

    // Central views

    // tabViews_ = new QTabWidget;
    tabViews_->setTabPosition(QTabWidget::South);

    editFileContent_ = new EditTextSource;
    tabViews_->addTab(editFileContent_, QString("File content"));
    viewStructure3D_ = new ViewStructure;
    tabViews_->addTab(viewStructure3D_, QString("Structure"));
    viewElements_ = new TableElements;
    tabViews_->addTab(viewElements_, QString("Elements"));

    setCentralWidget(tabViews_);

    setupActions();
    setupDockingViews();
    createStatusBar();

    readSettings();

    connect(editFileContent_->document(), &QTextDocument::contentsChanged,
            this, &FrameBrowser::documentWasModified);

    setUnifiedTitleAndToolBarOnMac(true);

    this->updateUi();
}

void FrameBrowser::tile(const QMainWindow *previous)
{
    if (!previous)
        return;
    int topFrameWidth = previous->geometry().top() - previous->pos().y();
    if (!topFrameWidth)
        topFrameWidth = 40;
    const QPoint pos = previous->pos() + 2 * QPoint(topFrameWidth, topFrameWidth);
    if (QApplication::desktop()->availableGeometry(this).contains(rect().bottomRight() + pos))
        move(pos);
}

void FrameBrowser::setupDockingViews()
{
    viewFiles_= new ViewFilesystem;

  QDockWidget *pInit;
  QDockWidget *pNext;
  pInit = new QDockWidget(tr("Files"), this);
  pInit->setWidget(viewFiles_);
  // pNext = new QDockWidget(tr("Workspace"), this);
  this->addDockWidget(Qt::LeftDockWidgetArea, pInit);
} 

//! [implicit tr context]
void FrameBrowser::setupActions()
{
//! [implicit tr context]
    QToolBar *fileToolBar = addToolBar(tr("File"));
    // QToolBar *pTool = this->toolBar();

    const QIcon iconNew = QIcon::fromTheme("document-new", QIcon(":/images/New.png"));
    actionNew_->setIcon(iconNew);
    actionNew_->setShortcuts(QKeySequence::New);
    actionNew_->setStatusTip(tr("Create a new file"));
    fileToolBar->addAction(actionNew_);

    const QIcon iconOpen = QIcon::fromTheme("document-open", QIcon(":/images/Open.png"));
    actionOpen_->setIcon(iconOpen);
    actionOpen_->setShortcuts(QKeySequence::Open);
    actionOpen_->setStatusTip(tr("Open an existing file"));
    fileToolBar->addAction(actionOpen_);

    const QIcon iconSave = QIcon::fromTheme("document-save", QIcon(":/images/Save.png"));
    actionSave_->setIcon(iconSave);
    actionSave_->setShortcuts(QKeySequence::Save);
    actionSave_->setStatusTip(tr("Save the document to disk"));
    fileToolBar->addAction(actionSave_);

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
    connect(actionClose_, &QAction::triggered, this, &QWidget::close);

    const QIcon iconExit = QIcon::fromTheme("application-exit", QIcon(":/images/Exit.png"));
    actionExit_->setIcon(iconExit);
    actionExit_->setShortcuts(QKeySequence::Quit);
    connect(actionExit_, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    actionExit_->setStatusTip(tr("Exit the application"));

    // QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

#ifndef QT_NO_CLIPBOARD
    const QIcon iconCut = QIcon::fromTheme("edit-cut", QIcon(":/images/Cut.png"));
    actionCut_->setIcon(iconCut);
    actionCut_->setShortcuts(QKeySequence::Cut);
    actionCut_->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(actionCut_, &QAction::triggered, editFileContent_, &EditTextSource::cut);

    const QIcon iconCopy = QIcon::fromTheme("edit-copy", QIcon(":/images/Copy.png"));
    actionCopy_->setIcon(iconCopy);
    actionCopy_->setShortcuts(QKeySequence::Copy);
    actionCopy_->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(actionCopy_, &QAction::triggered, editFileContent_, &EditTextSource::copy);

    const QIcon iconPaste = QIcon::fromTheme("edit-paste", QIcon(":/images/Paste.png"));
    actionPaste_->setIcon(iconPaste);
    actionPaste_->setShortcuts(QKeySequence::Paste);
    actionPaste_->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(actionPaste_, &QAction::triggered, editFileContent_, &EditTextSource::paste);

    editToolBar->addAction(actionCut_);
    editToolBar->addAction(actionCopy_);
    editToolBar->addAction(actionPaste_);

    menuBar()->addSeparator();
#endif // !QT_NO_CLIPBOARD

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
    connect(editFileContent_, &EditTextSource::copyAvailable, actionCut_, &QAction::setEnabled);
    connect(editFileContent_, &EditTextSource::copyAvailable, actionCopy_, &QAction::setEnabled);
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
    if (!editFileContent_->document()->isModified())
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

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    editFileContent_->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
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
    QSettings settings(QCoreApplication::organizationName()
    , QCoreApplication::applicationName());
    const int count = settings.beginReadArray(recentFilesKey());
    settings.endArray();
    return count > 0;
}

void FrameBrowser::prependToRecentFiles(const QString &fileName)
{
    QSettings settings(QCoreApplication::organizationName()
    , QCoreApplication::applicationName());

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    setRecentFilesVisible(!recentFiles.isEmpty());
}

void FrameBrowser::updateRecentFileActions()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

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
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << editFileContent_->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void FrameBrowser::setCurrentFile(const QString &fileName)
{
    static int sequenceNumber = 1;

    bHasNoFile_ = fileName.isEmpty();
    if (bHasNoFile_) {
        curFile = tr("document%1.txt").arg(sequenceNumber++);
    } else {
        curFile = QFileInfo(fileName).canonicalFilePath();
    }

    editFileContent_->document()->setModified(false);
    setWindowModified(false);

    if (!bHasNoFile_ && windowFilePath() != curFile)
        FrameBrowser::prependToRecentFiles(curFile);

    setWindowFilePath(curFile);
}

QString FrameBrowser::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

FrameBrowser *FrameBrowser::findMainWindow(const QString &fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        FrameBrowser *mainWin = qobject_cast<FrameBrowser *>(widget);
        if (mainWin && mainWin->curFile == canonicalFilePath)
            return mainWin;
    }

    return 0;
}

void FrameBrowser::clearContent()
{
    editFileContent_->clear();
    editFileContent_->document()->setModified(true);
}

void FrameBrowser::clearPath()
{
    curFile = QString();
    bHasNoFile_ = true;
}

void FrameBrowser::on_actionNew__triggered()
{
    this->newFile();
}

void FrameBrowser::on_actionOpen__triggered()
{
    auto flags = QFileDialog::DontUseNativeDialog | QFileDialog::DontUseCustomDirectoryIcons;
    QString flt_open; // // tabViews_->describeOpenFormats();
    QString *flt_sel = nullptr;
    QMessageBox::about(this, tr("Open a file"), tr("Trying to open a file"));
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
    QString sPath = curFile;
    this->loadFile(curFile);
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
     this->save(); 
}

void FrameBrowser::on_actionSaveAs__triggered() 
{ 
    this->saveAs(); 
}

void FrameBrowser::on_actionClearAll__triggered()
{
    QMessageBox::about(this, tr("Clear all"), tr("Clear all current content of the document") );
    this->clearContent();
}

void FrameBrowser::on_actionAbout__triggered()
{
    // FrameInfo info(this);
    // info.showModal();
    QMessageBox::about(this, tr("ScDrv Text Browser")
    , tr("The <b>ScDrv</b> software parses structure text files to find molecular structures.<br>\
It makes use of the <b>SDI</b> example that demonstrates<br>\
how to write single document interface applications using Qt."));
}

void FrameBrowser::on_actionAboutQt__triggered()
{ 
    qApp->aboutQt();
}
