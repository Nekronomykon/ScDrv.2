#ifndef View_Filesystem_h
#define View_Filesystem_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QSplitter>

#include "BrowseFiles.h"
#include "BrowseFilesystem.h"

#include <QModelIndex>

class ViewFilesystem
    : public QSplitter
{
  Q_OBJECT
public:
  explicit ViewFilesystem(QWidget* /*parent*/ = nullptr);
  ~ViewFilesystem() override = default;

public slots:
  void listDirectoryIndex(const QModelIndex& /*idx*/);
private:
  QPointer<BrowseFilesystem> browse_dir_; // should see and select only dirs to make it current
  QPointer<BrowseFiles> list_files_; // should see and select only regular files in current dir
};

#endif // !View_Filesystem_h
