#include "orderitemdata.h"
#include "ui_orderitemdata.h"

OrderItemData::OrderItemData(QString id,QString name,QString category,QString prc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderItemData)
{
    ui->setupUi(this);
    ui->lblId->setText(id);
    ui->lblName->setText(name);
    ui->lblCategory->setText(category);
    ui->lblRate->setText(prc);
}

OrderItemData::~OrderItemData()
{
    delete ui;
}


void OrderItemData::on_pushButton_clicked()
{
    //TO-DO
}
