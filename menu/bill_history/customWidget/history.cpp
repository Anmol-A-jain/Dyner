#include "history.h"
#include "ui_history.h"
#include "data/globaldata.h"
<<<<<<< HEAD
=======
#include "../billhistorywidget.h"
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
#include "../DialogBox/orderdata.h"

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

    GlobalData::setShadow(this);
    GlobalData::setShadow(ui->btnReport,QColor(255,0,0));
<<<<<<< HEAD
=======
 //  static_cast<BillHistoryWidget*>(myparent)->updateTotalSales();

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
}

History::~History()
{
    delete ui;
}

<<<<<<< HEAD
=======
double History::getTotal()
{
    return (ui->lblamt->text().toDouble());

}

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
void History::on_btnReport_clicked()
{
    Orderdata repoetDialog(ui->lblId->text().toInt(),ui->lblName->text(),ui->lblDate->text());
    repoetDialog.exec();
}
