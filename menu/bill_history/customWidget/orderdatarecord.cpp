#include "orderdatarecord.h"
#include "ui_orderdatarecord.h"
#include "data/globaldata.h"

orderDataRecord::orderDataRecord(QString id,QString name,QString category,QString qty,QString price,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderDataRecord)
{
    ui->setupUi(this);

    ui->lblId->setText(id);
    ui->lblQty->setText(qty);
    ui->lblName->setText(name);
    ui->lblRate->setText(price);
    ui->lblCategory->setText(category);

    GlobalData::setShadow(this);
}

orderDataRecord::~orderDataRecord()
{
    delete ui;
}
