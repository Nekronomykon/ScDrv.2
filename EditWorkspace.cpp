#include "EditWorkspace.h"

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QFileInfoList>
#include <QFileIconProvider>

#include <QListWidgetItem>

EditWorkspace::EditWorkspace(QWidget *parent)
    : _Base(parent)
{
  QFileIconProvider provide;
  this->setWindowIcon(provide.icon(QFileIconProvider::Folder));
}

bool EditWorkspace::addFilePath(const QString &path)
{
  QListWidgetItem *pFileItem = nullptr;
  QFileInfo finfo(path);

  if (!finfo.isFile())
    return false;

  bool result(false);
  QString s_query = finfo.canonicalFilePath();

  QList<QListWidgetItem *> added = this->findItems(s_query, Qt::MatchExactly);

  if (added.isEmpty())
  {
    QFileIconProvider icons;
    QIcon ic(icons.icon(finfo));
    pFileItem = new QListWidgetItem(ic, s_query, this);
    // set pFrame as data??
    result = true;
  }
  else
  {
    pFileItem = added.front(); // and the only item, I hope...
  }

  return result;
}

void EditWorkspace::listDir(const QString &dir_path, bool bRecurse)
{
  QDir dir_entry(dir_path);

  QFileInfoList fi_list = dir_entry.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Readable, QDir::Name);
  foreach (QFileInfo fi, fi_list)
  {
    this->addFilePath(fi.canonicalFilePath());
  }
  if (bRecurse)
  {
    fi_list = dir_entry.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);
    foreach (QFileInfo fi, fi_list)
      this->listDir(fi.canonicalFilePath(), true);
  }
}
