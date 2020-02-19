#include "displaywidget.h"
#include "ui_displaywidget.h"
#include <QDebug>
#include <QSqlQuery>
#include "data/databasecon.h"
#include "../orderwidget.h"
#include <QMessageBox>

displayWidget::displayWidget(QString id,QString name, QString category, double Qty, double price, int tblNo ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::displayWidget)
{
    ui->setupUi(this);

    this->flag = false;

    ui->btnDelete->setText(QString("\U0001F5D1"));

    this->amt = Qty * price ;
    this->tblNo = tblNo;

    ui->lblId->setText(id);
    ui->lblName->setText(name);
    ui->lblCategory->setText(category);
    ui->doubleSpinBox->setValue(Qty);
    ui->lblPrice->setText(QString::number(price));
    ui->lblamt->setText(QString::number(this->amt));

    myparent = parent;
}

displayWidget::~displayWidget()
{
    delete ui;
}

double displayWidget::getTotal()
{
    return (ui->lblPrice->text().toDouble() * ui->doubleSpinBox->text().toDouble() );
}

void displayWidget::setFlag(bool flag)
{
    this->flag = flag;
}

void displayWidget::on_doubleSpinBox_valueChanged(double arg1)
{

    if(this->flag == true)
    {
        double amt = arg1 * ui->lblPrice->text().toDouble() ;
        ui->lblamt->setText(QString::number(amt));

        databaseCon d;
        QString cmd = "UPDATE tblTempOrder SET qty = '"+ui->doubleSpinBox->text()+"' WHERE item_id = '"+ui->lblId->text()+"' AND table_no ="+ QString::number(tblNo) +" " ;//"SELECT * FROM tblTempOrder";
        QSqlQuery* q = d.execute(cmd);

        qDebug() << "displayWidget.cpp (on_doubleSpinBox_valueChanged) : value changed " << arg1;

        delete q;

        static_cast<OrderWidget*>(myparent)->updateTotalAmmount();
    }
}

void displayWidget::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Delete", "Do You Want To Delete " + ui->lblName->text() ,QMessageBox::No|QMessageBox::Yes,QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        databaseCon d;

        QString cmd = "DELETE FROM tblTempOrder WHERE item_id = '"+ ui->lblId->text() +"'" ;
        QSqlQuery* q = d.execute(cmd);
        delete q;
        static_cast<OrderWidget*>(this->myparent)->loadData();
    }
}
