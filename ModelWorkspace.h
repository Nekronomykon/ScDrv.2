#ifndef Model_Workspace_h
#define Model_Workspace_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include "FrameFile.h"
#include <QAbstractListModel>
#include <QVariant>

#include <QVector>
#include <QPair>
class ModelWorkspace
    : public QAbstractListModel
{
  Q_OBJECT
public:
  ModelWorkspace();
  ~ModelWorkspace() override;

  int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;

private:
  QVector<
};

#endif // !Model_Workspace_h
