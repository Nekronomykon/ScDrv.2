#ifndef Browse_Filesystem_h
#define Browse_Filesystem_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QTreeView>

#include "ModelTextFiles.h"

class BrowseFiles
  : public QTreeView
{
  Q_OBJECT
public:
  explicit BrowseFiles(QWidget* /*parent*/ = nullptr);
  ~BrowseFiles() override;

private:
  QPointer<ModelTextFiles> model_txt_;
};

#endif // !Browse_Filesystem_h
