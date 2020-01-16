#ifndef ADDORDERITEM_H
#define ADDORDERITEM_H
#include "../customWidget/orderitemdata.h"
#include <QVector>
#include <QDialog>

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
    QVector<OrderItemData*> itemlist;
};

#endif // ADDORDERITEM_H
