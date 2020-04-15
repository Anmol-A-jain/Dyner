#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>
#include <QVector>
#include "customWidget/orderitemdata.h"
#include "customWidget/displaywidget.h"
#include <QRegExpValidator>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();
    int getTblNo();
    void loadData();
    void deleterVecterData();
    void deleteCustomerData();
    void resetTotalAmount();
    void updateTotalAmmount();
    int getOrderTypeIndex();

    void sendToDataKitchen(qint16 orderNo, qint16 tblNo, QString name);

    bool isOrderCompleted();

private slots:
    void on_cmbOrrderType_currentIndexChanged(int index);

    void on_cmbTblNo_currentTextChanged(const QString &arg1);

    void on_cmbOrrderType_currentTextChanged(const QString &arg1);

    void on_btnPlaceOrder_clicked();

    void on_btnAddOrder_clicked();

    void on_btnClear_clicked();

    void on_txtMblNo_textChanged(const QString &arg1);

    void on_txtCustName_textChanged(const QString &arg1);

    void on_btnStatus_clicked();

private:
    Ui::OrderWidget *ui;
    QVector<displayWidget*> list;
    QRegExpValidator* r1;
    QRegExpValidator* r2;

    QWidget* myParent;

};

#endif // ORDERWIDGET_H
