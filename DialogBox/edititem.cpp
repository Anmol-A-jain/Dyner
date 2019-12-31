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
    ui->txtcategory->addItem(category);
    ui->txtPrice->setValue(price);

    databaseCon d;
    QString cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        QString data =q->value("category").toString();

        if(data != category)
        {
            ui->txtcategory->addItem(data);
        }
    }

    delete q;
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
    QString category = ui->txtcategory->currentText();

    if(!id.isEmpty() && !name.isEmpty() && !price.isEmpty() && !category.isEmpty())
    {
        QString cmd = "UPDATE tblMenu SET itemName = '"+name+"' , category = '"+category+"' , Price = "+price + " where id = '"+id+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;
        static_cast<AdminWidget*>(myParent)->loadData();
    }
}
