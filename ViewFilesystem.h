#ifndef View_Filesystem_h
#define View_Filesystem_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QSplitter>
#include <QListWidget> // temporary

#include "BrowseFiles.h"


class ViewFilesystem
    : public QSplitter
{
  Q_OBJECT
public:
  ViewFilesystem(QWidget* parent = Q_NULLPTR);
  ~ViewFilesystem() override;

private:
  QPointer<QListWidget> list_files_; // should see and select only regular files in current dir
  QPointer<BrowseFiles> browse_dir_; // should see and select only dirs to make it current
};

#endif // !View_Filesystem_h
