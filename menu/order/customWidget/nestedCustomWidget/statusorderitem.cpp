#include "statusorderitem.h"
#include "ui_statusorderitem.h"

statusOrderItem::statusOrderItem(QString id,QString name,QString status, QString qty, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusOrderItem)
{
    ui->setupUi(this);
    this->id = id;
    this->name = name;
    this->status = status;
    this->qty = qty;

    ui->lblID->setText(id);
    ui->lblName->setText(name);
    ui->lblStatus->setText(status);
    ui->lblQty->setText(qty);

}

statusOrderItem::~statusOrderItem()
{
    delete ui;
}
