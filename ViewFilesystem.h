#ifndef View_File_System_h__
#define View_File_System_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QSplitter>

#include <QPointer>

#include <QFileSystemModel>
#include <QModelIndex>

#include <QTreeView>
#include <QListView>

class ViewFilesystem
    : public QSplitter
{
    Q_OBJECT
public:
    explicit ViewFilesystem(QWidget * /* parent */ = nullptr);

    QFileSystemModel* modelSystem() const{ return modelFileSystem_; }
    QTreeView* fileSystem() const { return treeFileSystem_; }
    QListView* getFileSelector() const { return listFiles_; }

    QFileInfo fileInfo(const QModelIndex&);

private slots:
    void listFilesAt(const QModelIndex &);

private:
    QPointer<QFileSystemModel> modelFileSystem_;
    QPointer<QTreeView> treeFileSystem_;
    QPointer<QListView> listFiles_;
};

#endif // !View_File_System_h__
