#ifndef ADDORDERITEM_H
#define ADDORDERITEM_H
#include "customWidgets/order/orderitemdata.h"
#include <QVector>
#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class AddOrderItem;
}

class AddOrderItem : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrderItem(QWidget *parent = nullptr);
    ~AddOrderItem();
    void loadData();
    void deleteVecterData();

private:
    Ui::AddOrderItem *ui;
    QWidget *myParent;
    QVBoxLayout *layout;
    QWidget *itemList;
    QVector<OrderItemData*> itemlist;
};

#endif // ADDORDERITEM_H
