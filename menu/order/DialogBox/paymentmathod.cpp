#include "paymentmathod.h"
#include "ui_paymentmathod.h"
#include "data/databasecon.h"
#include "data/globaldata.h"
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include "../orderwidget.h"
#include "dyner.h"
#include "server/mytcpsocket.h"


paymentMathod::paymentMathod(double amt,double discount,double tax,int tblno,QString custno,QString ordertype,QString custnm,QVector<displayWidget*> list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paymentMathod)
{
    ui->setupUi(this);
    myparent = parent;

    this->amt = amt;
    this->discount = discount;
    this->tax = tax;
    this->tblno = tblno;
    this->custno = custno;
    this->custnm = custnm;
    this->ordertype = ordertype;
    this->list = list;

    ui->btnCash->setText(QString("\U0001F4B8"));
    ui->btnCard->setText(QString("\U0001F4B3"));
}

paymentMathod::~paymentMathod()
{
    delete ui;
}

void paymentMathod::insertData(QString paymentType)
{
    if(!MyTcpSocket::getIsKitchenConnected())
    {
        QMessageBox::critical(this,"Critical","Kitchen Is Not Connected");
        return;
    }

    databaseCon d;

    QString cmd = "SELECT billId FROM mstTblBill ORDER BY billId desc LIMIT 1 " ;
    QSqlQuery* q = d.execute(cmd);

    bool isEmpty = false;
    int lastID = 10001;

    qDebug() << "orderwidget.cpp (insertData ) : Date : " << QDate::currentDate();

    if(q->next())
    {
        lastID = q->value("billId").toInt() + 1;
    }
    else
    {
        isEmpty = true;
    }

    // inserting bill in mstTblcust

    cmd = "SELECT * FROM mstTblcust WHERE custMblNo = " + this->custno;

    q = d.execute(cmd);

    if(!q->next())
    {
        cmd = "INSERT INTO mstTblcust VALUES('"+this->custno+"','"+this->custnm+"');";
        delete q;
        delete d.execute(cmd);
    }

    // inserting bill in mstTblBill
    QString netAmount = (QString::number(this->amt - (this->amt * this->discount/100) + this->tax ));
    QString discount = QString::number(this->discount);
    QString tax = QString::number(this->tax);

    QString date = QDate::currentDate().toString("yyyy-M-d");

    if(isEmpty)
    {
        QString startID = QString::number(lastID);
        cmd = "INSERT INTO mstTblBill VALUES("+startID+","+netAmount+","+discount+","+tax+",'"+paymentType+"','"+this->ordertype+"','"+date+"',"+this->custno+","+QString::number(this->tblno)+");" ;
    }
    else
    {
        cmd = "INSERT INTO mstTblBill VALUES("+QString::number(lastID)+","+netAmount+","+discount+","+tax+",'"+paymentType+"','"+this->ordertype+"','"+date+"',"+this->custno+","+QString::number(this->tblno)+");" ;
    }
    delete d.execute(cmd);

    for (int i = 0; i < list.count(); ++i)
    {
        struct OrderData orderData = list[i]->getData();

        QString id = orderData.id->text();
        QString name = orderData.name->text();
        QString qty = orderData.qty->text();
        QString price = orderData.price->text();
        QString category = orderData.category->text();

        QString billId = QString::number(lastID);

        cmd = "INSERT INTO tblBill VALUES("+billId+",'"+id+"','"+name+"',"+qty+",'"+price+"','"+category+"');" ;
        delete d.execute(cmd);
    }


    cmd = "DELETE FROM tblTempOrder WHERE table_no = "+QString::number(this->tblno)+";" ;
    delete d.execute(cmd);

    int orderLastID = 1;

    if(tblno != 0)
    {
        cmd = "DELETE FROM oderDataFromWaiter WHERE tblNo = "+QString::number(tblno)+" ";
        delete d.execute(cmd) ;
    }
    else
    {

        cmd =  "SELECT orderID FROM oderDataFromWaiter ORDER BY orderID desc LIMIT 1 " ;
        q = d.execute(cmd) ;

        if(q->next() )
        {
            orderLastID = q->value("orderID").toInt() + 1;
        }

        for (int i = 0; i < list.count(); ++i)
        {
            QString id;
            double qty;

            id = list.at(i)->getData().id->text();
            qty = list.at(i)->getData().qty->value();

            qDebug() << "OrderWidget (on_btnPlaceOrder_clicked) : item id : " << id;
            qDebug() << "OrderWidget (on_btnPlaceOrder_clicked) : item qty : " << qty;

            cmd = "INSERT INTO oderDataFromWaiter VALUES('"+id+"' ,"+QString::number(qty)+",'"+QString::number(tblno)+"','sending','',"+QString::number(orderLastID)+",'"+QString::number(lastID)+"' );";
            q = d.execute(cmd) ;
        }

        delete q;

        //OrderWidget* parent = static_cast<OrderWidget*>(myparent);
        //parent->sendToDataKitchen(orderLastID,tblno,custnm);
        Dyner::getServer()->sendToKitchenParentThread(orderLastID,tblno,custnm);
    }


    OrderWidget* parent = static_cast<OrderWidget*>(myparent);
    parent->deleterVecterData();
    parent->deleteCustomerData();
    parent->resetTotalAmount();

    QMessageBox::information(this,"Information","Order has been Placed by <span style='color:green'>"+paymentType+"</span>");

    QMessageBox::StandardButton reply = QMessageBox::information(this,"Print Bill","Do you want to print a copy of bill",QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No,QMessageBox::StandardButton::Yes);

    if(reply == QMessageBox::StandardButton::Yes)
    {
        QString totalAmount = QString::number(((this->amt )));
        GlobalData::printBill(custnm,lastID,totalAmount,tax,QString::number(this->discount*this->amt/100),netAmount,this);
    }

    this->accept();
}

void paymentMathod::on_btnCash_clicked()
{
    this->insertData("Cash");
}

void paymentMathod::on_btnCard_clicked()
{
    this->insertData("Card");
}
