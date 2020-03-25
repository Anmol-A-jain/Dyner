#include "statusdialogbox.h"
#include "ui_statusdialogbox.h"
#include "../customWidget/orderdatawidget.h"
#include "data/databasecon.h"

StatusDialogBox::StatusDialogBox(int tblno, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusDialogBox)
{
    ui->setupUi(this);
    myParent = parent;
    this->tblno = tblno;


    if(tblno != 0)
    {
        ui->orderNoList->hide();
        this->setWindowTitle("table Order Status : " + QString::number(tblno));

        databaseCon d;
        QString cmd = "SELECT DISTINCT orderID FROM oderDataFromWaiter WHERE tblNo = "+QString::number(tblno)+"" ;
        QSqlQuery* q = d.execute(cmd);

        while (q->next())
        {
            int orderNo = q->value("orderID").toInt();
            orderDataWidget* item = new orderDataWidget(orderNo);
            ui->orderContainer->addWidget(item);
            list.push_back(item);
        }
        delete q;
    }
    else
    {
        this->setWindowTitle("table Order Status : parcel ");
        databaseCon d;
        QString cmd = "SELECT DISTINCT orderID FROM oderDataFromWaiter WHERE tblNo = "+QString::number(tblno)+"" ;
        QSqlQuery* q = d.execute(cmd);

        while (q->next())
        {
            QString tag = q->value("orderID").toString();
            ui->orderNoList->addItem(tag);
        }
        delete q;
    }



}

StatusDialogBox::~StatusDialogBox()
{
    deleteVectorData();
    delete ui;
}

void StatusDialogBox::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

void StatusDialogBox::on_orderNoList_currentIndexChanged(const QString &arg1)
{
    deleteVectorData();
    this->setWindowTitle("table Order Status : " + QString::number(tblno));
    orderDataWidget* item = new orderDataWidget(arg1.toInt());
    ui->orderContainer->addWidget(item);
    list.push_back(item);
}

void StatusDialogBox::on_btnComplete_clicked()
{
    databaseCon d;
    QString cmd = "DELETE FROM oderDataFromWaiter WHERE orderID = "+ui->orderNoList->currentText()+"";
    delete d.execute(cmd);
}
