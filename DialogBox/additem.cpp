#include "additem.h"
#include "ui_additem.h"
#include <data/databasecon.h>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

addItem::addItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);

    ui->category->clear();
    databaseCon d;
    QString cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        ui->category->addItem(q->value("category").toString());
    }
    delete q;

    cmd = "SELECT id FROM tblMenu ORDER BY id" ;
    q = d.execute(cmd);


    while(q->next())
    {
        QString str = q->value("id").toString();
        int len = str.length(), i = 0;

        for(QChar &ch : str )
        {
            ++i;
            if(i == len)
            {
                if(ch == '9')
                {
                    ch = '0';
                }
                else
                {
                    ch = ch.unicode() + 1;
                }
            }
        }

        ui->id->setText(str);
    }
    delete q;

}

addItem::~addItem()
{
    delete ui;
}

void addItem::on_btnAdd_clicked()
{
    databaseCon d;

    QString id = ui->id->text();

    QString cmd = "SELECT * FROM tblMenu WHERE id = '"+id+"' " ;

    QSqlQuery* q = d.execute(cmd);
    while (q->next())
    {
        QMessageBox::warning(this,"Error","Item Id : "+id+" is already assign to \""+q->value("itemName").toString()+"\"\nCategory : "+q->value("category").toString()+"\nPrice : "+q->value("Price").toString()+"");
        return;
    }
    delete q;

    QString name = ui->name->text();
    QString price = ui->price->text();
    QString category = ui->category->currentText();

    if(!id.isEmpty() && !name.isEmpty() && !price.isEmpty() && !category.isEmpty() )
    {
        cmd = "insert into tblMenu values('" + id + "','" + name + "'," + price + " ,'" + category + "')" ;
        q = d.execute(cmd);
        delete q;

        QMessageBox::information(this,"Item Added","Item "+name+" has been added");
        this->accept();
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
