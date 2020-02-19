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
}

OrderItemData::~OrderItemData()
{
    delete ui;
}


void OrderItemData::on_btnAddOrder_clicked()
{
    databaseCon d;

    int tblNo = static_cast<OrderWidget*>(myparent)->getTblNo();
    QString cmd = "select * from tblTempOrder WHERE table_no =" + QString::number(tblNo) ;

    QSqlQuery* q = d.execute(cmd);

    while (q->next())
    {
        if(q->value("item_id").toString() == ui->lblId->text() )
        {
            cmd = "UPDATE tblTempOrder SET qty = '"+ui->doubleSpinBox->text()+"' WHERE item_id = '"+ui->lblId->text()+"' ";
            q = d.execute(cmd);
            delete q;
            QMessageBox::information(this,"Info","Quantity has been updated");
            static_cast<OrderWidget*>(myparent)->loadData();
            return;
        }
    }

    cmd = "INSERT INTO tblTempOrder VALUES("+QString::number(tblNo)+",'"+ui->lblId->text()+"','"+ui->doubleSpinBox->text()+"')" ;

    q = d.execute(cmd);
    QMessageBox::information(this,"Info","Item Added");

    delete q;    
    static_cast<OrderWidget*>(myparent)->loadData();
}
