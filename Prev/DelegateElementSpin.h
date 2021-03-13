#ifndef DELEGATEELEMENTSPIN_H
#define DELEGATEELEMENTSPIN_H

#include <QObject>
#include <QWidget>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QStyleOptionViewItem>

#include <QStyledItemDelegate>

class DelegateElementSpin
    : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit DelegateElementSpin(QObject* /*parent*/ = nullptr);

  QWidget *createEditor(QWidget* /*parent*/, const QStyleOptionViewItem & /*option*/
                        , const QModelIndex &/*index*/) const override;

  void setEditorData(QWidget* /*editor*/, const QModelIndex & /*index*/) const override;
  void setModelData(QWidget* /*editor*/, QAbstractItemModel * /*model*/
                    , const QModelIndex &/*index*/) const override;

  void updateEditorGeometry(QWidget* /*editor*/, const QStyleOptionViewItem & /*option*/
                            , const QModelIndex &/*index*/) const override;

};

#endif // DELEGATEELEMENTSPIN_H
