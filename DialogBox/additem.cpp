#include "additem.h"
#include "ui_additem.h"
#include <databasecon.h>
#include <QDir>
#include <QDebug>

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

    QString file = QDir::currentPath() + "/DynerDB.db" ;
    databaseCon d;
    QString cmd = "insert into tblMenu values('" + ui->id->text() + "','" + ui->name->text() + "'," + ui->price->text() + " ,' " + ui->category->text() + "')" ;
    d.excequte(cmd);
}
