#include "paymentmathod.h"
#include "ui_paymentmathod.h"
#include "data/databasecon.h"
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include "../orderwidget.h"

paymentMathod::paymentMathod(double netamt,double discount,double tax,int tblno,QString custno,QString ordertype,QString custnm,QVector<displayWidget*> list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paymentMathod)
{
    ui->setupUi(this);
    myparent = parent;

    this->netamt = netamt;
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
        delete d.execute(cmd);
    }

    // inserting bill in mstTblBill
    QString netAmount = QString::number(this->netamt);
    QString discount = QString::number(this->discount);
    QString tax = QString::number(this->tax);

    QString year = QString::number(QDate::currentDate().year());
    QString month = QString::number(QDate::currentDate().month());
    QString day = QString::number(QDate::currentDate().day());

    QString date = year+"-"+month+"-"+day;

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

    for (int i = 0; i < list.count(); ++i) {
        struct OrderData orderData = list[i]->getData();

        QString id = orderData.id->text();
        QString name = orderData.name->text();
        QString qty = orderData.qty->text();
        QString price = orderData.price->text();
        QString category = orderData.category->text();

        QString billId = QString::number(lastID);

        cmd = "INSERT INTO tblBill VALUES("+billId+","+id+",'"+name+"',"+qty+",'"+price+"','"+category+"');" ;
        delete d.execute(cmd);
    }


    cmd = "DELETE FROM tblTempOrder WHERE table_no = "+QString::number(this->tblno)+";" ;
    delete d.execute(cmd);

    OrderWidget* parent = static_cast<OrderWidget*>(myparent);
    parent->deleterVecterData();
    parent->deleteCustomerData();
    parent->resetTotalAmount();

    QMessageBox::information(this,"Information","Order has been Placed by <span style='color:green'>"+paymentType+"</span>");
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
