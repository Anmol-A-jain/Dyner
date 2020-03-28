#include "orderdatawidget.h"
#include "ui_orderdatawidget.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include "../orderwidget.h"
#include "nestedCustomWidget/statusorderitem.h"
#include "dyner.h"
#include "../DialogBox/statusdialogbox.h"
#include <QDebug>
#include <QMessageBox>

orderDataWidget::orderDataWidget(int orderNo, int tblNo,QWidget *grandParent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderDataWidget)
{
    ui->setupUi(this);
    GlobalData::setShadow(this);
    myParent = parent;
    myGrandParent = grandParent;

    this->orderNo = orderNo;
    this->tblNo = tblNo;
    ui->btnDelete->setText(QString("\U0001F5D1"));

//    if(tblNo == 0)
//    {
//        ui->btnDelete->hide();
//    }

    ui->label->setText(ui->label->text().append(QString::number(orderNo)));

    databaseCon d;

    //QSqlDatabase &database = databaseCon::getDatabase();
    QString cmd = "SELECT a.*,b.itemName FROM oderDataFromWaiter a LEFT JOIN mstTblMenu b ON a.Item_id = b.id WHERE orderID = "+QString::number(orderNo)+"" ;
    QSqlQuery* q = d.execute(cmd);
    //QSqlQuery* q = new QSqlQuery(database); //d.execute(cmd);

    enum column{i_id,iqty,itblNumber,istatus,inote,iorderID,Billid,iName};

    if(q->exec(cmd))
    {
        while (q->next())
        {
            QString id = q->value(i_id).toString();
            status = q->value(istatus).toString();
            QString itemName = q->value(iName).toString();
            QString qty = q->value(iqty).toString();

            statusOrderItem* item = new statusOrderItem(id,itemName,qty,this);
            ui->orderItemContainer->addWidget(item);
            list.push_back(item);
        }
    }
    else
    {
        qDebug() << "OrderItemData (OrderItemData) : not execute :" << cmd;
    }

    ui->lblStatus->setText(ui->lblStatus->text() + status);

    delete q;

    if(status == "finished")
    {
        GlobalData::setShadow(this,QColor(255,0,0),0,10);
        ui->btnDelete->hide();
    }
    if(status == "accepted")
    {
        GlobalData::setShadow(this,QColor(67, 134, 244),0,10);
        ui->btnDelete->hide();
    }

    connect(Dyner::getServer(),SIGNAL(updateStatusInOrderWidget(QString,int)),this,SLOT(updateStatus(QString,int)));
}

orderDataWidget::~orderDataWidget()
{
    deleteVectorData();
    delete ui;
}

void orderDataWidget::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

QString orderDataWidget::getStatus() const
{
    databaseCon d;
    QString cmd = "SELECT a.*,b.itemName FROM oderDataFromWaiter a LEFT JOIN mstTblMenu b ON a.Item_id = b.id WHERE orderID = "+QString::number(orderNo)+"" ;
    QSqlQuery* q = d.execute(cmd);

    enum column{i_id,iqty,itblNumber,istatus,inote,iorderID,iName};

    q->next();

    QString status = q->value(istatus).toString();
    return status;
}

void orderDataWidget::updateStatus(QString status, int orderNo)
{
    if(this->orderNo != orderNo)
    {
        return;
    }

    if(status == "finished")
    {
        GlobalData::setShadow(this,QColor(255,0,0),0,10);
    }
    if(status == "accepted")
    {
        GlobalData::setShadow(this,QColor(67, 134, 244),0,10);
    }

    qDebug() << "orderDataWidget (updateStatus) : status :" << status;
    ui->lblStatus->setText("Status : " + status);

    ui->btnDelete->hide();
}

void orderDataWidget::on_btnDelete_clicked()
{
    int reply = QMessageBox::critical(this,"Delete order",
                          "Do you want to delete this order.\nOrder no: " + QString::number(this->orderNo)
                          ,QMessageBox::StandardButton::No|QMessageBox::StandardButton::Yes,QMessageBox::StandardButton::No);

    if(reply == QMessageBox::StandardButton::Yes)
    {
        databaseCon d;
        QString cmd ;

        for (int i = 0; i < list.count(); ++i)
        {
            QString id = list.at(i)->getId();
            QString qty = list.at(i)->getQty();

            cmd = "UPDATE tblTempOrder SET qty = ((SELECT qty FROM tblTempOrder WHERE item_id = '"+id+"'  AND table_no = "+QString::number(tblNo)+")-"+qty+") WHERE item_id = '"+id+"'  AND table_no = "+QString::number(tblNo)+"";
            delete d.execute(cmd);
        }

        if(tblNo == 0)
        {
            cmd = "SELECT DISTINCT BillID  FROM oderDataFromWaiter WHERE orderID = "+QString::number(this->orderNo)+" ";
            QSqlQuery* q = d.execute(cmd);
            int billID = 0;
            while(q->next())
            {
                billID = q->value(0).toInt();
            }
            cmd = "DELETE FROM oderDataFromWaiter WHERE BillID = "+QString::number(billID)+" ";
            delete d.execute(cmd);
        }
        else
        {
            cmd = "DELETE FROM oderDataFromWaiter WHERE orderID = "+QString::number(this->orderNo)+"" ;
            delete d.execute(cmd);
            static_cast<OrderWidget*>(myGrandParent)->loadData();
        }



        QMessageBox::information(this,"order Deleted","Order has been deleted success fully");
        emit refresh();

        //static_cast<StatusDialogBox*>(myParent)->loadData();
        qDebug() << "orderDataWidget (on_btnDelete_clicked) : delete order :";

        DynerServer* server = Dyner::getServer();
        server->deleteOrderSignal(orderNo);
    }
}
