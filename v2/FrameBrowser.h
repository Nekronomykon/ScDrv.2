#ifndef FrameBrowser_h__
#define FrameBrowser_h__

#include <QMainWindow>
#include <QList>

#include "ViewFilesystem.h"

#include "EditTextSource.h"
#include "ViewStructure.h"

#include "ui_FrameBrowser.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTabWidget;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition with macro]
class FrameBrowser 
  : public QMainWindow
  , private Ui_FrameBrowser
{
    Q_OBJECT

public:
    explicit FrameBrowser(QWidget* /* parent */, const QString &fileName); // to dismiss:
    // separated into two consequtive steps: [0] creation; [1]: file attachment / content loading
//! [class definition with macro]
    explicit FrameBrowser(QWidget* /* parent */ = nullptr);

    static FrameBrowser* createForPath(const QString& /* fileName*/, QWidget* /* parent */ = nullptr);
    static FrameBrowser *findByPath(const QString &fileName);

    void tile(const QWidget *previous);

    ViewStructure* getView3D() const {return viewStructure3D_; }

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // void open();
    void updateRecentFileActions();
    void openRecentFile();
    void documentWasModified();

    // menuFile_
    void on_actionNew__triggered();     // [New]            --> create a new empty file browser frame
    //
    void on_actionClone__triggered();   // [Clone]          --> make this frame unattached to any file path 
                                        // with 'modified' flag set. An easy means of copying content to edit ;)
    //
    void on_actionOpen__triggered();    // [Open]           --> query for a file path; while it is obtained and valid, 
                                        // and if this frame is attached already to a path or modified, try 
                                        // to find it opened already and still unmodified; if such not found,
                                        // create a new browser frame, attach it to the path and then read its content 
                                        // as the data text source. 
                                        // Otherwise, attach the path to this frame and read its content as the data text source.
    //
    void on_actionReload__triggered();  // [Reload]         --> meaningful if this frame is attached to a valid file path; 
                                        // If so, and if it is modified, query for the changes to be abandoned. 
                                        // If Ok, save its current path, do [Clear all], attach the path (again) 
                                        // to this frame and read its content as the data source.
                                        // If Retry, save its current path, create a new browser frame, attach it 
                                        // to the path and read its content as the data source. 
                                        // if Cancel, cancel it ;)
    //
    void on_actionSave__triggered();    // [Save]           --> meaningful if modified flag is set here;
                                        // If frame is unattached, do [Save as]; otherwise replace the content 
                                        // of the attached path with the current source dump, 
                                        // clear the 'modified' flag and create a new source dump 
    //
    void on_actionSaveAs__triggered();  // [Save as]        --> query for the valid file path, possibly nonexistent;
                                        // If successful, and path is writable, rename/move accordingly the current 
                                        // source dump, clear the 'modified' flag and create a new source dump
    //
    void on_actionClose__triggered();    // [Close]          --> trying to close this browser frame
    //
    void on_actionExit__triggered();     // [Exit]           --> trying to close all browser frames    
    //
    // menuEdit_
    void on_actionClearAll__triggered();    // [Clear all]  --> remove / empty all data from this frame.
                                            // If path is attached, modified flag is set; otherwise is is cleared
    // menuView_
    // menuMolecule_
    // menuTools_
    void on_actionOptions__triggered(); // [Options]        --> the most common form of setup...
    // menuHelp_
    void on_actionAbout__triggered();   // [About]      --> show the info box / screen / frame of the program
    void on_actionAboutQt__triggered(); // [About At]   --> show the Qt information box

private:
    enum { MaxRecentFiles = 9 };

    FrameBrowser* createNewFrame();

    bool attachToPath(const QString& filePath, bool bDelaySync = false);

    bool save();
    bool saveAs();

    void clearContent();
    void clearPath();

    void setupActions();
    void setupToolBar();
    void setupDockingViews();

    void updateUi();

    void init();
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void openFile(const QString &fileName);
    void loadFile(const QString &fileName);
    static bool hasRecentFiles();
    void prependToRecentFiles(const QString &fileName);
    void setRecentFilesVisible(bool visible);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    static QString strippedName(const QString &fullFileName);

    ViewFilesystem *viewFiles_;

    // QTabWidget *tabViews_;

    // EditTextSource *editFileContent_;
    ViewStructure *viewStructure3D_;

    QAction *recentFileActs[MaxRecentFiles];
    QAction *recentFileSeparator;
    QAction *recentFileSubMenuAct;

    bool bHasNoFile_; // flag to determine the binding to a file path
    QString curFile;  // path to a corresponding file
};

#endif // ! FrameBrowser_h__

