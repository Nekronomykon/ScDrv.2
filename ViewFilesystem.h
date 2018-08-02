#ifndef __Browse_Filesystem_h__
#define __Browse_Filesystem_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QPointer>
#include <QTreeView>

#include "ModelTextFiles.h"

class ViewFilesystem
  : public QTreeView
{
  Q_OBJECT
public:
  explicit ViewFilesystem(QWidget* /*parent*/ = nullptr);
  ~ViewFilesystem() override;

private:
  QPointer<ModelTextFiles> model_txt_;
};

#endif // !__Browse_Filesystem_h__
