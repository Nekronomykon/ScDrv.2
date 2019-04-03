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
  void on_actionNew__triggered();
  void on_actionOpen__triggered();
  //
  void on_actionExportScene__triggered();
  void on_actionExportCoords__triggered();
  //
  void on_actionToggleLayout__triggered();
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

  void loadPathContentFrom(const QString &);
  void setSceneBackground(const QString &);

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

  void updateUi();

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

  QPointer<ComboBoxColors> colors_back_;

private slots:
};

#endif // !Frame_Workspace_h
