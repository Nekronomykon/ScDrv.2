#include "DelegateElements.h"

#include "TableElements.h"

DelegateElements::DelegateElements()
  : QStyledItemDelegate()
{}

QWidget* DelegateElements::createEditor(QWidget *parent
  , const QStyleOptionViewItem &/* option */
  , const QModelIndex &/* index */) const
        {
          TableElements* pTable = new TableElements(parent);

          return pTable;
        }

void DelegateElements::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void DelegateElements::setModelData(QWidget *editor, QAbstractItemModel *model,
  const QModelIndex &index) const
{

}

void DelegateElements::updateEditorGeometry(QWidget *editor
  , const QStyleOptionViewItem &option
  , const QModelIndex &index) const
{
  TableElements* pTable = static_cast<TableElements*>(editor);
}
