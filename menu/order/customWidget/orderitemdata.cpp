#include "orderitemdata.h"
#include "ui_orderitemdata.h"
#include "data/databasecon.h"
#include "../orderwidget.h"

OrderItemData::OrderItemData(QString id,QString name,QString category,QString prc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderItemData)
{
    ui->setupUi(this);
    myparent = parent;

    ui->lblId->setText(id);
    ui->lblName->setText(name);
    ui->lblCategory->setText(category);
    ui->lblRate->setText(prc);
}

OrderItemData::~OrderItemData()
{
    delete ui;
}


void OrderItemData::on_btnAddOrder_clicked()
{
    int tblNo = static_cast<OrderWidget*>(myparent)->getTblNo();
    databaseCon d;
    QString cmd = "INSERT INTO tblTempOrder VALUES("+ QString::number(tblNo) +",'"+ui->lblId->text()+"','"+ui->doubleSpinBox->text()+"')" ;
    QSqlQuery* q = d.execute(cmd);

    delete q;
}
