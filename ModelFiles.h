#ifndef Model_Files_h
#define Model_Files_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QFileSystemModel>

class ModelFiles
  : public QFileSystemModel
{
  Q_OBJECT
public:
  explicit ModelFiles();
  ~ModelFiles() override;

  int columnCount(const QModelIndex&) const override;
};

#endif // !Model_Files_h
