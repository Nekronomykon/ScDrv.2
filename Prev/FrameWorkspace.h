#ifndef Frame_Workspace_h
#define Frame_Workspace_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>
#include <QMap>

#include <QEvent>
#include <QCloseEvent>
#include <QPrinterInfo>

#include <QProgressBar>

#include "ViewWorkspace.h"
#include "ViewFilesystem.h"
#include "ViewFileContent.h"
#include "FrameFile.h"

#include "ComboBoxColors.h"

#include <QMainWindow>
#include "ui_FrameWorkspace.h"

class FrameWorkspace
    : public QMainWindow,
      private Ui_FrameWorkspace
{
  Q_OBJECT
public:
  enum
  {
    MaxRecentFiles = 9
  };

  typedef FrameFile Child;
  typedef Child::TypeFileName FileName;
  typedef Child::FileContext FileFormat;

  explicit FrameWorkspace(QWidget * /*parent*/ = Q_NULLPTR);
  ~FrameWorkspace() override = default;

  static int hasRecentFiles();

  void openAllFiles(const QStringList &);
  void loadFileContents(const QString &);

  Child *getActiveChild() const;

  // general...
  void addPathToWorkspace(const QString & /*arg */, bool /*bOpen*/ = false);
  // and classified:

  //----------------------------------------------------------------------------------------
  // addFileToWorkspace(path, to_open) : adds path to the workspace, immediately try to open
  //                                   : if requested. It is assumed that 'path' contains
  //                                   : the fully qualified (absolute) path to a file
  //----------------------------------------------------------------------------------------
  //                           Returns : pointer to a corresponding FrameFile object,
  //                                   : if there is any
  //----------------------------------------------------------------------------------------
  Child *addFileToWorkspace(const QString & /* path */, FileFormat /*fmt*/ = FileFormat());
  Child *addLinkToWorkspace(const QString & /* path */, bool /* bOpen */ = false);

  //----------------------------------------------------------------------------------------
  // addDirToWorkspace(path, to_recurse) : adds all files in the dir pointed by 'path'
  //                                     : to the workspace, subdirs are added recursively
  //                                     : if requested. It is assumed that 'path' contains
  //                                     : the fully qualified (absolute) path to a dir
  //                             Returns : (none)
  //----------------------------------------------------------------------------------------
  void addDirToWorkspace(const QString & /*dir*/, bool /* bRecurse */ = false);

public slots:
  //
protected slots:
  //
  void loadPathContentFrom(const QString &);
  void setSceneBackground(const QString &);
  void setSceneMultisample(int);

protected:
  void changeEvent(QEvent *e) override;
  void closeEvent(QCloseEvent *event) override;

  Child *provideFileFrame(const QString &);

  // functions:
private:
  void restoreSettings();
  void storeSettings();

  void setupActions();
  void setupToolBars();
  void setupDockingViews();

  void initRecentActions();

  void updateUi(); // check the state and update UI

  // data members:
private slots:

  void openRecentFile();
  void updateRecentFilesMenu();

private:
  QAction *recentFileActs[MaxRecentFiles];

  QPointer<ModelWorkspace> model_workspace_;
  QPointer<ViewWorkspace> edit_workspace_;
  QPointer<ViewFilesystem> view_files_;
  QPointer<ViewFileContent> view_file_content_;

  QPointer<QProgressBar> progress_;

  QPointer<ComboBoxColors> colors_back_; // background color name
  QPointer<QComboBox> level_AA_;         // antialiasing

  // QPointer<QPrinterInfo> printer_info_;

private slots:
  // most common actions generally finished ;)
  void on_actionExit__triggered();    // [Exit]       --> trying to close all browser frames and finalize the program
  void on_actionAbout__triggered();   // [About]      --> show the info box / screen / frame of the program
  void on_actionAboutQt__triggered(); // [About At]   --> show the Qt information box

  // next actions, by menu:
  // menuFile_
  void on_actionNew__triggered();   // [New]            --> create a new empty file browser frame
  void on_actionClone__triggered(); // [Clone]          --> make this frame unattached to any file path
                                    // with 'modified' flag set. An easy means of copying content to edit ;)
  //
  void on_actionOpen__triggered(); // [Open]           --> query for a file path; while it is obtained and valid,
                                   // and if this frame is attached already to a path or modified, try
                                   // to find it opened already and still unmodified; if such not found,
                                   // create a new browser frame, attach it to the path and then read its content
                                   // as the data text source.
                                   // Otherwise, attach the path to this frame and read its content as the data text source.
  //
  void on_actionReload__triggered(); // [Reload]         --> meaningful if this frame is attached to a valid file path;
                                     // If so, and if it is modified, query for the changes to be abandoned.
                                     // If Ok, save its current path, do [Clear all], attach the path (again)
                                     // to this frame and read its content as the data source.
                                     // If Retry, save its current path, create a new browser frame, attach it
                                     // to the path and read its content as the data source.
                                     // if Cancel, cancel it ;)
  //
  void on_actionExportScene__triggered(); // [Export --> Scene] --> save the current scene into an image file:
  void on_actionExportCoords__triggered();
  //
  void on_actionPrint__triggered();
  void on_actionPageSetup__triggered();
  //
  void on_actionClose__triggered(); // [Close]          --> trying to close this browser frame
  //
  //
  // menuEdit_
  void on_actionClearAll__triggered(); // [Clear all]  --> remove / empty all data from this frame.
                                       // If path is attached, modified flag is set; otherwise is is cleared
  // menuView_
  void on_actionOptions__triggered(); // [Options]        --> the most common form of setup...
                                      // menuHelp_
  // menuView_
  void on_actionToggleLayout__triggered(); // [Toggle Layout] --> toggle RTL <=> LTR UI Layout...
  //
  void on_actionSourceEdit__triggered();
  void on_actionSourceCast__triggered();
  //
  void on_actionProjOrthogonal__triggered();
  void on_actionProjPerspective__triggered();
  //
  void on_actionMolFast__triggered();
  void on_actionMolBalls__triggered();
  void on_actionMolStick__triggered();
  void on_actionMolSpace__triggered();
  //
  // menuTools_
  void on_actionSetFont__triggered();
  // menuFile_
  //
};

#endif // !Frame_Workspace_h
