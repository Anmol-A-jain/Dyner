#include "statusdialogbox.h"
#include "ui_statusdialogbox.h"
#include "../customWidget/orderdatawidget.h"
#include "data/databasecon.h"
#include <QMessageBox>

StatusDialogBox::StatusDialogBox(int tblno, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusDialogBox)
{
    ui->setupUi(this);
    myParent = parent;
    this->tblno = tblno;

    loadData();
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
        list[i]->deleteLater();
    }
    list.clear();
}

void StatusDialogBox::loadData()
{
    deleteVectorData();
    if(tblno != 0)
    {
        ui->btnComplete->hide();
        ui->orderNoList->hide();
        this->setWindowTitle("table Order Status : " + QString::number(tblno));

        databaseCon d;
        QString cmd = "SELECT DISTINCT orderID FROM oderDataFromWaiter WHERE tblNo = "+QString::number(tblno)+"" ;
        QSqlQuery* q = d.execute(cmd);

        while (q->next())
        {
            int orderNo = q->value("orderID").toInt();
            orderDataWidget* item = new orderDataWidget(orderNo,tblno,myParent);
            ui->orderContainer->addWidget(item);
            list.push_back(item);
            connect(item,SIGNAL(refresh()),this,SLOT(refresh()));
        }
        delete q;
    }
    else
    {
        ui->orderNoList->clear();
        this->setWindowTitle("table Order Status : parcel ");
        databaseCon d;
        QString cmd = "SELECT DISTINCT orderID FROM oderDataFromWaiter WHERE tblNo = "+QString::number(tblno)+" ORDER BY orderID DESC" ;
        QSqlQuery* q = d.execute(cmd);

        while (q->next())
        {
            QString tag = q->value("orderID").toString();
            ui->orderNoList->addItem(tag);
        }
        delete q;
    }

}

void StatusDialogBox::on_orderNoList_currentIndexChanged(const QString &arg1)
{
    deleteVectorData();

    orderDataWidget* item = new orderDataWidget(arg1.toInt(),tblno);
    ui->orderContainer->addWidget(item);
    list.push_back(item);

    connect(item,SIGNAL(refresh()),this,SLOT(refresh()));
}

void StatusDialogBox::on_btnComplete_clicked()
{

    if(ui->orderNoList->currentText().toInt() == 0 && tblno == 0)
    {
        QMessageBox::information(this,"Empty","No order to complete");
        return;
    }

    for (int i = 0; i < list.count(); ++i)
    {
        if(list.at(i)->getStatus() != "finished" )
        {
            QMessageBox::warning(this,"Order Not Prepared","All Order Of This Bill Not Has Been Completed");
            return;
        }
    }

    databaseCon d;
    QString cmd = "DELETE FROM oderDataFromWaiter WHERE orderID = "+ui->orderNoList->currentText()+"";
    delete d.execute(cmd);

    loadData();
}

void StatusDialogBox::refresh()
{
    loadData();
}
