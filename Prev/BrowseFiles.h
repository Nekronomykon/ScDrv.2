#ifndef Browse_Files_h
#define Browse_Files_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QListView> 

#include "ImplModelView.h"
#include "ModelFiles.h"

class BrowseFiles
  : public ImplModelView<BrowseFiles, QListView, ModelFiles>
{
  typedef  ImplModelView<BrowseFiles, QListView, ModelFiles> _Base;

  Q_OBJECT
public:
  explicit BrowseFiles(QWidget* /*parent*/ = nullptr);
  ~BrowseFiles() override = default;

public slots:

private:
};

#endif // !Browse_Files_h
