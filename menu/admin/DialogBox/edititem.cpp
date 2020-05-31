#include "edititem.h"
#include "ui_edititem.h"
#include "data/databasecon.h"
#include "../adminwidget.h"
#include <QSqlQuery>
#include <QMessageBox>

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

void EditItem::on_btnUpdate_clicked()
{
    databaseCon d;

    QString id = ui->txtId->text();
    QString name = ui->txtName->text();
    QString price = ui->txtPrice->text();
    QString category = ui->txtcategory->currentText();

    if(!id.isEmpty() && !name.isEmpty() && !price.isEmpty() && !category.isEmpty())
    {
        QString cmd = "UPDATE mstTblMenu SET itemName = '"+name+"' , category = '"+category+"' , Price = "+price + " where id = '"+id+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;
        static_cast<AdminWidget*>(myParent)->loadData();
        QMessageBox::information(this,"Information","Item Data Has Been Updated");
        emit this->accept();
    }
    else
    {
        QString errormsg = "Following Fields are emply : \n";
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
        QMessageBox::critical(this,"Error",errormsg);
    }
}
