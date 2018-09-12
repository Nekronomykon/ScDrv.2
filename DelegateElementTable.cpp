#include "DelegateElementTable.h"

#include "TableElements.h"

DelegateElementTable::DelegateElementTable()
  : QStyledItemDelegate()
{}

QWidget* DelegateElementTable::createEditor(QWidget *parent
  , const QStyleOptionViewItem &/* option */
  , const QModelIndex &/* index */) const
        {
          TableElements* pTable = new TableElements(parent);

          return pTable;
        }

void DelegateElementTable::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void DelegateElementTable::setModelData(QWidget *editor, QAbstractItemModel *model,
  const QModelIndex &index) const
{

}

void DelegateElementTable::updateEditorGeometry(QWidget *editor
  , const QStyleOptionViewItem &option
  , const QModelIndex &index) const
{
  TableElements* pTable = static_cast<TableElements*>(editor);
}
