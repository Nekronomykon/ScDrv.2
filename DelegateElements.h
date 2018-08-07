#ifndef DELEGATEELEMENTS_H
#define DELEGATEELEMENTS_H

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>
#include <QModelIndex>
#include <QStyleOptionViewItem>

#include <QStyledItemDelegate>

class DelegateElements
    : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit DelegateElements();

  QWidget* createEditor(QWidget* /*parent*/,
        const QStyleOptionViewItem &/* option */,
        const QModelIndex & /*index*/) const override;

  void setEditorData(QWidget */*editor*/
    , const QModelIndex &/*index*/) const override;

  void setModelData(QWidget* /*editor*/
    , QAbstractItemModel* /*model*/
    , const QModelIndex & /*index*/) const override;

  void updateEditorGeometry(QWidget* /*editor*/,
      const QStyleOptionViewItem &/*option*/
    , const QModelIndex &/*index*/) const override;
};

#endif // DELEGATEELEMENTS_H
