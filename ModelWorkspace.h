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
#include <QMap>

class ModelWorkspace
    : public QAbstractListModel
{
  Q_OBJECT
public:
  typedef FrameFile Child;
  typedef Child::TypeFileName FileName;
  typedef Child::FileContext  FileFormat;
  typedef QVector<QPair<FileName, FileFormat> > Workspace;

  explicit ModelWorkspace();
  ~ModelWorkspace() override;

  int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

private:
  Workspace workspace_;
};

#endif // !Model_Workspace_h
