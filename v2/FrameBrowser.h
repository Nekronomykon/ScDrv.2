#ifndef FrameBrowser_h__
#define FrameBrowser_h__

#include <QMainWindow>
#include <QList>

#include "ViewFilesystem.h"

#include "EditTextSource.h"
#include "ViewStructure.h"
#include "TableElements.h"

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
    FrameBrowser(QWidget* /* parent */ = nullptr);
//! [class definition with macro]
    explicit FrameBrowser(QWidget* /* parent */, const QString &fileName);

    void tile(const QMainWindow *previous);

    EditTextSource* getEditText() const {return editFileContent_;}
    ViewStructure* getView3D() const {return viewStructure3D_; }
    TableElements* getViewElements() const {return viewElements_;}

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    FrameBrowser* newFile();
    // void open();
    void updateRecentFileActions();
    void openRecentFile();
    void documentWasModified();

    // menuFile_
    void on_actionNew__triggered();
    void on_actionClone__triggered();
    //
    void on_actionOpen__triggered();
    void on_actionReload__triggered();
    //
    void on_actionSave__triggered();
    void on_actionSaveAs__triggered();
    // menuEdit_
    void on_actionClearAll__triggered();
    // menuHelp_
    void on_actionAbout__triggered();
    void on_actionAboutQt__triggered();

private:
    enum { MaxRecentFiles = 9 };

    bool save();
    bool saveAs();

    void clearContent();
    void clearPath();

    void setupActions();
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
    FrameBrowser *findMainWindow(const QString &fileName) const;

    ViewFilesystem *viewFiles_;

    // QTabWidget *tabViews_;

    EditTextSource *editFileContent_;
    ViewStructure *viewStructure3D_;
    TableElements* viewElements_;

    QAction *recentFileActs[MaxRecentFiles];
    QAction *recentFileSeparator;
    QAction *recentFileSubMenuAct;

    QString curFile;
    bool bHasNoFile_; // flag to determine the binding to a file path
};

#endif // ! FrameBrowser_h__

