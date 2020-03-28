#include "orderdata.h"
#include "ui_orderdata.h"
#include "data/databasecon.h"

Orderdata::Orderdata(int billID, QString name, QString date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Orderdata)
{
    ui->setupUi(this);
    this->billID = billID;

    ui->lblName->setText(ui->lblName->text().append(name));
    ui->lblDate->setText(ui->lblDate->text().append(date));
    ui->lblBillId->setText(ui->lblBillId->text().append(QString::number(billID)));

    databaseCon d;
    QString cmd = "SELECT * FROM tblBill WHERE billId = "+QString::number(billID)+"";
    QSqlQuery* q = d.execute(cmd);

    while (q->next())
    {
        QString id = q->value("itemId").toString();
        QString name = q->value("ItemName").toString();
        QString qty = q->value("QTY").toString();
        QString price = q->value("price").toString();
        QString category = q->value("category").toString();

        orderDataRecord* reccord = new orderDataRecord(id,name,category,qty,price);
        ui->widgetContainer->addWidget(reccord);
        list.push_back(reccord);
    }

}

Orderdata::~Orderdata()
{
    deleteVectorData();
    delete ui;
}

void Orderdata::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        list.at(i)->deleteLater();
    }
    list.clear();
}
