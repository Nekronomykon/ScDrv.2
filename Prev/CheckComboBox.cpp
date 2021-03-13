#include "CheckComboBox.h"

#include <QTimer>


CheckComboBox::CheckComboBox(QWidget *parent) : QComboBox(parent)
{
  setEditable(true);
  model = new QStandardItemModel;
  displayedit = "";
  itemcount = model->rowCount();
  updateText();
}

void CheckComboBox::showPopup()
{
  temp = new QStandardItemModel;
  temp = model;

  /*
if the user write somthing into the edit line, the new number of rows will be greater than the old number of rows:
the new items has to be set as checkable items and every item should be only one time in the list
*/
  if (itemcount < temp->rowCount())
  {
    for (int row = 0; row < model->rowCount(); row++) //for every item in the model set the new model
    {
      if (row == itemcount)
      {
        /*
Tests if more than one new item are added at the same time
*/
        QString string = this->itemText(row);
        QString pattern("; ");
        QStringList datalist = string.split(pattern);

        /*
if only one item was add:
set the item checked and add it to the model
*/
        if (datalist.count() == 1)
        {
          QStandardItem *newItem = new QStandardItem;
          newItem->setText(datalist.at(0));
          newItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          newItem->setData(Qt::Checked, Qt::CheckStateRole);
          model->setItem(row, 0, newItem);
          row++;
        }

        /*
if more than one item was written in the edit line:
test for similarity with the items in the current list
and add every new item as new single item to the model and will be checked
*/
        else {
          for (int size = 0; size < datalist.count(); size++)
          {
            QList<QStandardItem*> list = temp->findItems(datalist.at(size)); //check for similarity
            if (list.empty() == true)
            {

              QStandardItem *newItem = new QStandardItem;
              newItem->setText(datalist.at(size));
              newItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
              newItem->setData(Qt::Checked, Qt::CheckStateRole);
              model->setItem(row, 0, newItem);
              row++;
            }

          }
        }
      }

      /*
in case, that only the current available items were checked
*/
      else {
        QStandardItem *newItem = new QStandardItem;
        newItem->setText(this->itemText(row));
        newItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (temp->item(row, 0)->checkState() == Qt::Checked)
        {
          newItem->setData(Qt::Checked, Qt::CheckStateRole);
          // qDebug()<<"blubb";
        }
        else newItem->setData(Qt::Unchecked, Qt::CheckStateRole);
        model->setItem(row, 0, newItem);
      }
    }
  }

  // set the model of the combobox
  this->setModel(model);

  QComboBox::showPopup();

  // set the current number of items
  itemcount = model->rowCount();

}

void CheckComboBox::hidePopup()
{
  displayedit = "";
  for (int i = 0; i < model->rowCount(); i++)
  {
    if (model->item(i, 0)->checkState() == Qt::Checked)
    {
      displayedit = displayedit + model->item(i, 0)->text() + "; ";
    }

  }
  QComboBox::hidePopup();
  QTimer::singleShot(0, this, SLOT(updateText()));
  this->setToolTip(displayedit);
}

void CheckComboBox::addItem(const QString &text)
{
  int row = model->rowCount();
  item = new QStandardItem;
  item->setText(text);
  item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
  item->setData(Qt::Unchecked, Qt::CheckStateRole);
  model->setItem(row, 0, item);
  this->setModel(model);
  itemcount = model->rowCount();
}

void CheckComboBox::addItems(const QStringList &texts)
{

  for (int i = 0; i < texts.count(); i++)
  {
    int row = model->rowCount();
    item = new QStandardItem;
    item->setText(texts.at(i));
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);
    model->setItem(row, 0, item);
    this->setModel(model);
  }
  itemcount = model->rowCount();
}

void CheckComboBox::updateText()
{
  this->lineEdit()->setText(displayedit);
}
