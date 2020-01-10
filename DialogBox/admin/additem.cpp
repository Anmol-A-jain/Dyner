#include "additem.h"
#include "header/menu/adminwidget.h"
#include "ui_additem.h"
#include <data/databasecon.h>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QKeyEvent>

addItem::addItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);

    int size = ui->category->height() - 5 ;

    ui->btnAddcategory->setMinimumSize(size,size);
    ui->btnAddcategory->setMaximumSize(size,size);

    this->loadCategory();

    databaseCon d;
    QString cmd = "SELECT id FROM tblMenu ORDER BY id" ;
    QSqlQuery* q = d.execute(cmd);

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


    myParent = parent;

    if(myParent)
    {
        if(ui->category->count() == 0)
        {
            QMessageBox::warning(this,"Warning","<h3>Empty Category List</h3>\nThere is no category available. please enter at least one category");
            static_cast<AdminWidget*>(myParent)->btnEditCategoryClicked();
            this->loadCategory();
        }

        cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
        q = d.execute(cmd);

        if(q->size() == 0)
        {
            QMessageBox::warning(this,"Warning","<h3>Empty Category List</h3>\nYou have not add any data in category.");

            QKeyEvent *event = new QKeyEvent( QEvent::KeyPress, Qt::Key_Escape ,Qt::NoModifier);
            QCoreApplication::postEvent (this, event);
        }
    }

    delete q;
}

addItem::~addItem()
{
    delete ui;
}

void addItem::loadCategory()
{
    ui->category->clear();
    databaseCon d;
    QString cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        ui->category->addItem(q->value("category").toString());
    }
    delete q;
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


void addItem::on_btnAddcategory_clicked()
{
    static_cast<AdminWidget*>(myParent)->btnEditCategoryClicked();
    this->loadCategory();
}
