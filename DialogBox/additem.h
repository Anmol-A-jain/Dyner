#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>

namespace Ui {
class addItem;
}

class addItem : public QDialog
{
    Q_OBJECT

public:
    explicit addItem(QWidget *parent = nullptr);
    ~addItem();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addItem *ui;
};

#endif // ADDITEM_H
