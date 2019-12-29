#include "additem.h"
#include "ui_additem.h"
#include <data/databasecon.h>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>

addItem::addItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);

}

addItem::~addItem()
{
    delete ui;
}

void addItem::on_buttonBox_accepted()
{
    databaseCon d;
    QString cmd = "insert into tblMenu values('" + ui->id->text() + "','" + ui->name->text() + "'," + ui->price->text() + " ,' " + ui->category->text() + "')" ;
    QSqlQuery* q = d.execute(cmd);
    if(q != nullptr)
    {
        delete q;
    }

}
