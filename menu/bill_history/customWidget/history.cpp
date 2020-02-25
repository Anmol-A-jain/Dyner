#include "history.h"
#include "ui_history.h"

History::History(int srNo, QString billId, QString custName, QString date, QString tblNo, QString orderType, QString paymentMethod, QString discount, QString tax, QString netAmount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);

    ui->lblSrNo->setText(QString::number(srNo));
    ui->lblId->setText(billId);
    ui->lblName->setText(custName);
    ui->lblDate->setText(date);
    ui->lblTblNo->setText(tblNo);
    ui->lblOrderType->setText(orderType);
    ui->lblPayment->setText(paymentMethod);
    ui->lblDisc->setText(discount);
    ui->lblTax->setText(tax);
    ui->lblamt->setText(netAmount);

}

History::~History()
{
    delete ui;
}
