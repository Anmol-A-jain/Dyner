#include "header/billhistorywidget.h"
#include "ui_billhistorywidget.h"

BillHistoryWidget::BillHistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillHistoryWidget)
{
    ui->setupUi(this);
}

BillHistoryWidget::~BillHistoryWidget()
{
    delete ui;
}
