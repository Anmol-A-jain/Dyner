#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class addItem;
}

class addItem : public QDialog
{
    Q_OBJECT

public:
    explicit addItem(QWidget *parent = nullptr);
    ~addItem();
    void loadCategory();

private slots:
    // inserting data to database  
    void on_btnAdd_clicked();

    void on_btnAddcategory_clicked();

private:
    Ui::addItem *ui;
    QWidget* myParent;
};

#endif // ADDITEM_H
