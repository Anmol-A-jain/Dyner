#include "header/menu/orderwidget.h"
#include "ui_orderwidget.h"
#include <QDebug>
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"

OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
    ui-> lblTblNo->hide();
    ui->cmbTblNo->hide();
    ui->lblAddres->hide();
    ui->cmbAdderess->hide();

    GlobalData g;
    int totalTable = XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable)).toInt();

    for (int i = 1 ; i <= totalTable ; ++i )
    {
        ui->cmbTblNo->addItem(QString::number(i));
    }
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::on_cmbOrrderType_currentIndexChanged(int index)
{
    qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : index : " << index;
    switch (index)
    {
        case 0:
        {
            // self pick up
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->hide();
            ui->cmbTblNo->hide();
            ui->lblAddres->hide();
            ui->cmbAdderess->hide();
            break;
        }
        case 1:
        {
            // Delivery
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->hide();
            ui->cmbTblNo->hide();
            ui->lblAddres->show();
            ui->cmbAdderess->show();
            break;
        }
        case 2:
        {
            // Table no
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->show();
            ui->cmbTblNo->show();
            ui->lblAddres->hide();
            ui->cmbAdderess->hide();
            break;
        }
    }
}
