#include "orderitemdata.h"
#include "ui_orderitemdata.h"
#include "data/databasecon.h"
#include "../orderwidget.h"
#include <QDebug>
#include <QMessageBox>
#include "data/globaldata.h"

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

    int tblNo = static_cast<OrderWidget*>(myparent)->getTblNo();

    QString cmd = "select * from tblTempOrder WHERE table_no =" + QString::number(tblNo) ;

    QSqlQuery* q = d.execute(cmd);

    while( q->next() )
    {

        QString myId = q->value("item_id").toString();
        double qty = q->value("qty").toDouble();
        if(id == myId)
        {
            ui->doubleSpinBox->setValue(qty);
        }
    }
    delete q;

    GlobalData::setShadow(this);
        GlobalData::setShadow(ui->btnAddOrder,QColor(67, 134, 244),0,10);
}

OrderItemData::~OrderItemData()
{
    delete ui;
}


void OrderItemData::on_btnAddOrder_clicked()
{
    databaseCon d;

    int tblNo = static_cast<OrderWidget*>(myparent)->getTblNo();
    QString cmd = "select * from tblTempOrder WHERE table_no =" + QString::number(tblNo) + " AND item_id = " + ui->lblId->text() ;
    QSqlQuery* q = d.execute(cmd);

    while (q->next())
    {
        if(ui->doubleSpinBox->text().toDouble() == 0.0)
        {
            cmd = "DELETE FROM tblTempOrder WHERE item_id = '"+ ui->lblId->text() +"'";
            QMessageBox::information(this,"Info","Item Has been Deleted");
        }
        else
        {
            cmd = "UPDATE tblTempOrder SET qty = '"+ui->doubleSpinBox->text()+"' WHERE item_id = '"+ui->lblId->text()+"' ";
            QMessageBox::information(this,"Info","Quantity has been updated");
        }
        q = d.execute(cmd);
        delete q;
        static_cast<OrderWidget*>(myparent)->loadData();
        return;
    }

    if(ui->doubleSpinBox->text().toDouble() == 0.0)
    {
        QMessageBox::warning(this,"Info","Please Enter value");
        return;
    }

    cmd = "INSERT INTO tblTempOrder VALUES("+QString::number(tblNo)+",'"+ui->lblId->text()+"','"+ui->doubleSpinBox->text()+"')" ;

    q = d.execute(cmd);
    QMessageBox::information(this,"Info","Item Added");

    delete q;    
    static_cast<OrderWidget*>(myparent)->loadData();
}
