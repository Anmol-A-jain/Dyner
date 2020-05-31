#include "statusorderitem.h"
#include "ui_statusorderitem.h"

statusOrderItem::statusOrderItem(QString id,QString name,QString qty, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusOrderItem)
{
    ui->setupUi(this);
    this->id = id;
    this->name = name;
    this->qty = qty;

    ui->lblID->setText(id);
    ui->lblName->setText(name);
    ui->lblQty->setText(qty);

}

statusOrderItem::~statusOrderItem()
{
    delete ui;
}

QString statusOrderItem::getId() const
{
    return id;
}

QString statusOrderItem::getQty() const
{
    return qty;
}
