#ifndef Browse_Filesystem_h
#define Browse_Filesystem_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QTreeView>

#include <QFileIconProvider>
#include "ModelFilesystem.h"

#include "ImplModelView.h"

class BrowseFilesystem :
  public  ImplModelView<BrowseFilesystem, QTreeView, ModelFilesystem>
{
  typedef ImplModelView<BrowseFilesystem, QTreeView, ModelFilesystem> _Base;

  Q_OBJECT
public:
  BrowseFilesystem(QWidget* /*parent*/ = nullptr);
  ~BrowseFilesystem() override = default;

  void SetupModel(ModelFilesystem* /*pM*/);
};

#endif // !Browse_Filesystem_h
