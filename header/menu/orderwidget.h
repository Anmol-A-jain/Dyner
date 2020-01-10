#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>
#include <customWidgets/order/orderitemdata.h>
#include <QVector>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();

private slots:
    void on_cmbOrrderType_currentIndexChanged(int index);

    void on_pushButton_clicked();

     QVector<OrderItemData> orderStore ;

private:
    Ui::OrderWidget *ui;
};

#endif // ORDERWIDGET_H
