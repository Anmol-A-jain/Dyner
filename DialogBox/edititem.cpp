#include "edititem.h"
#include "ui_edititem.h"
#include "data/databasecon.h"
#include "header/menu/adminwidget.h"
#include <QSqlQuery>

EditItem::EditItem(QString id,QString name,QString category, double price ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditItem)
{
    ui->setupUi(this);
    this->myParent = parent;

    ui->txtId->setText(id);
    ui->txtName->setText(name);
    ui->txtcategory->setText(category);
    ui->txtPrice->setValue(price);
}

EditItem::~EditItem()
{
    delete ui;
}

void EditItem::on_buttonBox_accepted()
{
    databaseCon d;

    QString id = ui->txtId->text();
    QString name = ui->txtName->text();
    QString price = ui->txtPrice->text();
    QString category = ui->txtcategory->text();

    if(!id.isEmpty() && !name.isEmpty() && !price.isEmpty() && !category.isEmpty())
    {
        QString cmd = "UPDATE tblMenu SET itemName = '"+name+"' , category = '"+category+"' , Price = "+price + " where id = '"+id+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;
        static_cast<AdminWidget*>(myParent)->loadData();
    }
}
