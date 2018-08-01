#ifndef __Frame_Wkspace_h__
#define __Frame_Wkspace_h__

#include <QPointer>
#include <QEvent>
#include <QCloseEvent>

#include "EditWorkspace.h"


#include "FrameFile.h"

#include "ui_FrameWkspace.h"
#include <QMainWindow>

class FrameWkspace
	: public QMainWindow
	, private Ui_FrameWkspace
{
  Q_OBJECT
public:

  typedef FrameFile Child;

  explicit FrameWkspace(QWidget* /*parent*/ = Q_NULLPTR);

  // general...
  void addPathToWorkspace(const QString & /*arg */, bool /*bOpen*/);
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

protected:
  void changeEvent(QEvent *e);
  void closeEvent(QCloseEvent *event);

  // functions:
private:
  void restoreSettings();
  void storeSettings();

	// data members:
private:
  QPointer<EditWorkspace> edit_workspace_;

private slots:
};

#endif // !__Frame_Wkspace_h__
