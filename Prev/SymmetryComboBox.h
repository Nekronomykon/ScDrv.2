#ifndef SYMMETRYCOMBOBOX_H
#define SYMMETRYCOMBOBOX_H

#include <QWidget>

#include <QComboBox>

class SymmetryComboBox
    : public QComboBox
{
  Q_OBJECT
public:
  explicit SymmetryComboBox(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SYMMETRYCOMBOBOX_H
