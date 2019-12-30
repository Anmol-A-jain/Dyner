#include "additem.h"
#include "ui_additem.h"
#include <data/databasecon.h>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

addItem::addItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);

    ui->category->clear();
    databaseCon d;
    QString cmd = "SELECT category FROM categoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        ui->category->addItem(q->value("category").toString());
    }

    delete q;

}

addItem::~addItem()
{
    delete ui;
}

void addItem::on_buttonBox_accepted()
{
    databaseCon d;
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/img/img/icon1.png"));

    QString id = ui->id->text();
    QString name = ui->name->text();
    QString price = ui->price->text();
    QString category = ui->category->currentText();

    if(!id.isEmpty() && !name.isEmpty() && !price.isEmpty() && !category.isEmpty() )
    {
        QString cmd = "insert into tblMenu values('" + id + "','" + name + "'," + price + " ,' " + category + "')" ;
        QSqlQuery* q = d.execute(cmd);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Item has been added to menu");
        msgBox.exec();
        delete q;
    }
    else
    {
        QString errormsg = "Item Has Not Been Added : ";

        if(id.isEmpty())
        {
            errormsg.append("\nPlease enter Id");
        }
        if(name.isEmpty())
        {
            errormsg.append("\nPlease enter Name");
        }
        if(category.isEmpty())
        {
            errormsg.append("\nPlease enter Categoty");
        }

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(errormsg);
        msgBox.exec();
    }
}
