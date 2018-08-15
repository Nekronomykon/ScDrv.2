#ifndef CHECKCOMBOBOX_H
#define CHECKCOMBOBOX_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QWidget>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>

class CheckComboBox : public QComboBox
{
  Q_OBJECT
public:
  explicit CheckComboBox(QWidget* /*parent*/ = Q_NULLPTR);

  void showPopup();
  void hidePopup();
  void addItem(const QString &text);
  void addItems(const QStringList &texts);

public slots:
  void updateText();

private:
  QString str;
  QStandardItemModel *model;
  QStandardItemModel *temp;
  QStandardItem *item;
  QString displayedit;
  QStringList list;
  int itemcount;
  bool check;
};

#endif // CHECKCOMBOBOX_H
