#include "billreqwidget.h"
#include "ui_billreqwidget.h"

BillReqWidget::BillReqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillReqWidget)
{
    ui->setupUi(this);
}

BillReqWidget::~BillReqWidget()
{
    delete ui;
}
