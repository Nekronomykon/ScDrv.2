#ifndef Browse_Filesystem_h
#define Browse_Filesystem_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QTreeView>

class BrowseFilesystem :
  public QTreeView
{
public:
  BrowseFilesystem(QWidget* /*parent*/ = nullptr);
  ~BrowseFilesystem() override = default;
};

#endif // !Browse_Filesystem_h
