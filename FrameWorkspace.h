#ifndef Frame_Workspace_h
#define Frame_Workspace_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>

#include <QEvent>
#include <QCloseEvent>

#include "ViewWorkspace.h"
#include "BrowseFiles.h"
#include "FrameFile.h"

#include "ui_FrameWorkspace.h"
#include <QMainWindow>

class FrameWorkspace
    : public QMainWindow
    , private Ui_FrameWorkspace
{
  Q_OBJECT
public:

  typedef FrameFile Child;

  explicit FrameWorkspace(QWidget* /*parent*/ = Q_NULLPTR);

  Child* getActiveChild() const;

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
  Child* addFileToWorkspace(const QString & /* path */, bool /* bOpen */ = false);
  Child* addLinkToWorkspace(const QString & /* path */, bool /* bOpen */ = false);

  //----------------------------------------------------------------------------------------
  // addDirToWorkspace(path, to_recurse) : adds all files in the dir pointed by 'path'
  //                                     : to the workspace, subdirs are added recursively
  //                                     : if requested. It is assumed that 'path' contains
  //                                     : the fully qualified (absolute) path to a dir
  //                             Returns : (none)
  //----------------------------------------------------------------------------------------
  void   addDirToWorkspace(const QString & /*dir*/, bool /* bRecurse */ = false);

public slots:
  //
protected slots:
  void on_actionOpen__triggered();

  void showPathContent(const QString&);

protected:
  void changeEvent(QEvent *e);
  void closeEvent(QCloseEvent *event);

  // functions:
private:
  void restoreSettings();
  void storeSettings();

  // data members:
private:
  QPointer<ViewWorkspace>  edit_workspace_;
  QPointer<BrowseFiles> view_files_;

private slots:
};

#endif // !Frame_Workspace_h
