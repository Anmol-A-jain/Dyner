#ifndef ORDERITEMDATA_H
#define ORDERITEMDATA_H

#include <QWidget>

namespace Ui {
class OrderItemData;
}

class OrderItemData : public QWidget
{
    Q_OBJECT

public:
    explicit OrderItemData(QString id,QString name,QString category,QString prc,QWidget *parent = nullptr);
    ~OrderItemData();

private slots:

    void on_btnAddOrder_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::OrderItemData *ui;
    QWidget *myparent;
};

#endif // ORDERITEMDATA_H
