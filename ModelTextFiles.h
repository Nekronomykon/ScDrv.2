#ifndef __Model_TextFiles_h__
#define __Model_TextFiles_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QFileSystemModel>

#include <QModelIndexList>

class ModelTextFiles
  : public QFileSystemModel
{
  Q_OBJECT
public:
  explicit ModelTextFiles();
  ~ModelTextFiles() override;

  int columnCount(const QModelIndex&) const override;
};

#endif // !__Model_TextFiles_h__
