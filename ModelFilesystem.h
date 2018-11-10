#ifndef Model_Filesystem_h
#define Model_Filesystem_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QFileSystemModel>

class ModelFilesystem
  : public QFileSystemModel
{
  Q_OBJECT
public:
  explicit ModelFilesystem() = default;
  ~ModelFilesystem() override = default;

  int columnCount(const QModelIndex&) const override;
};

#endif // !Model_Filesystem_h
