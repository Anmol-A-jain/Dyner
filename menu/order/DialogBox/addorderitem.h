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
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_menuColumn_currentIndexChanged(int index);

    void on_btnSearch_clicked();

    void on_SearchTextBox_returnPressed();

    void on_SearchTextBox_textChanged(const QString &arg1);

private:
    Ui::AddOrderItem *ui;
    QWidget *myParent;
    QVector<OrderItemData*> itemlist;
};

#endif // ADDORDERITEM_H
