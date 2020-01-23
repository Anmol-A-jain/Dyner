#include "orderitemdata.h"
#include "ui_orderitemdata.h"
#include "data/databasecon.h"
#include "../orderwidget.h"
#include <QDebug>
#include <QMessageBox>

OrderItemData::OrderItemData(QString id,QString name,QString category,QString prc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderItemData)
{
    ui->setupUi(this);
    myparent = parent;

    ui->lblId->setText(id);
    ui->lblName->setText(name);
    ui->lblCategory->setText(category);
    ui->lblRate->setText(prc);

    databaseCon d;
    QString cmd = "select * from tblTempOrder" ;
    QSqlQuery* q = d.execute(cmd);

    while( q->next() )
    {

        QString myId = q->value("item_id").toString();
        double qty = q->value("qty").toDouble();
        int myTblNo = q->value("table_no").toInt();
        int tblNo = static_cast<OrderWidget*>(myparent)->getTblNo();

        if(id == myId && myTblNo == tblNo)
        {
            qDebug() << "orderwidget.cpp (OrderItemData) :id == myId";
            qDebug() << "orderwidget.cpp (OrderItemData) :  myid : "<< myId << " qty : " << qty;
            ui->doubleSpinBox->setValue(qty);
        }
    }

    delete q;

}

OrderItemData::~OrderItemData()
{
    delete ui;
}


void OrderItemData::on_btnAddOrder_clicked()
{
    int tblNo = static_cast<OrderWidget*>(myparent)->getTblNo();
    databaseCon d;

    QString cmd = "SELECT * FROM tblTempOrder";
    QSqlQuery* q = d.execute(cmd);

    while (q->next())
    {
        int currentTblNo = q->value("table_no").toInt();
        if( currentTblNo == tblNo )
        {
            if(q->value("item_id").toString() == ui->lblId->text() )
            {
                cmd = "UPDATE tblTempOrder SET qty = '"+ui->doubleSpinBox->text()+"' WHERE item_id = '"+ui->lblId->text()+"' AND table_no ="+ QString::number(tblNo) +" ";
                q = d.execute(cmd);
                delete q;
                //QMessageBox::information(this,"Info","Quantity is updated");
                static_cast<OrderWidget*>(myparent)->loadData();
                return;
            }
        }
    }

    cmd = "INSERT INTO tblTempOrder VALUES("+ QString::number(tblNo) +",'"+ui->lblId->text()+"','"+ui->doubleSpinBox->text()+"')" ;
    q = d.execute(cmd);
    QMessageBox::information(this,"Info","Item Added");

    delete q;    
    static_cast<OrderWidget*>(myparent)->loadData();
}

void OrderItemData::on_doubleSpinBox_valueChanged(double arg1)
{

    qDebug() << "orderwidget.cpp (on_doubleSpinBox_valueChanged) : value from DB : " << arg1;
    emit on_btnAddOrder_clicked();
}
