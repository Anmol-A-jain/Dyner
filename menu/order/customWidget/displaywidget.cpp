#include "displaywidget.h"
#include "ui_displaywidget.h"
#include <QDebug>
#include <QSqlQuery>
#include "data/databasecon.h"
#include "menu/order/orderwidget.h"

displayWidget::displayWidget(QString id,QString name, QString category, double Qty, double price, int tblNo ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::displayWidget)
{
    ui->setupUi(this);

    this->id = id;
    this->idString = "<p align='center'>"+id+"</p>";
    this->name = "<p align='center'>"+name+"</p>";
    this->category = "<p align='center'>"+category+"</p>";
    this->price = price;
    this->Qty = Qty;
    this->amt = Qty * price ;
    this->tblNo = tblNo;

    QString protoPrice = "<p align='center'>"+QString::number(price)+"</p>";
    QString protoAmt = "<p align='center'>"+QString::number(this->amt)+"</p>";

    ui->lblId->setText(this->idString);
    ui->lblName->setText(this->name);
    ui->lblCategory->setText(this->category);
    ui->doubleSpinBox->setValue(this->Qty);
    ui->lblPrice->setText(protoPrice);
    ui->lblamt->setText(protoAmt);

    myparent = parent;
}

displayWidget::~displayWidget()
{
    delete ui;
}

void displayWidget::on_doubleSpinBox_valueChanged(double arg1)
{
    double amt = arg1 * this->price ;
    ui->lblamt->setText("<p align='center'>"+QString::number(amt)+"</p>");

    databaseCon d;
    QString cmd = "UPDATE tblTempOrder SET qty = '"+ui->doubleSpinBox->text()+"' WHERE item_id = '"+this->id+"' AND table_no ="+ QString::number(tblNo) +" " ;//"SELECT * FROM tblTempOrder";
    QSqlQuery* q = d.execute(cmd);

    qDebug() << "displayWidget.cpp (on_doubleSpinBox_valueChanged) : value changed " << arg1;

    /*while (q->next())
    {
        int currentTblNo = q->value("table_no").toInt();
        if( currentTblNo == tblNo )
        {
            if(q->value("item_id").toString() == ui->lblId->text() )
            {
                cmd = "UPDATE tblTempOrder SET qty = '"+ui->doubleSpinBox->text()+"' WHERE item_id = '"+ui->lblId->text()+"' AND table_no ="+ QString::number(tblNo) +" ";
                q = d.execute(cmd);
                delete q;
                return;
            }
        }
    }*/
    delete q;
}
