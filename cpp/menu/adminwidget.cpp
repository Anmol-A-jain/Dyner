#include "header/menu/adminwidget.h"
#include "ui_adminwidget.h"
#include "data/databasecon.h"
#include "DialogBox/additem.h"
#include "DialogBox/edittablenoanddiscount.h"
#include "DialogBox/editcategory.h"
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);

    this->loadData();
    this->loadInfo();
}

void AdminWidget::loadData()
{
    this->deleteVecterData();
    databaseCon d;
    QString cmd = "select * from tblMenu order by id" ;
    QSqlQuery* q = d.execute(cmd);
    while( q->next())
    {
        ItemWidget *item = new ItemWidget(this);
        itemlist.push_back(item);
        item->setData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString());
        ui->itemListContainer->addWidget(item);
    }
    delete q;
}

void AdminWidget::loadInfo()
{
    GlobalData g;
    ui->noOfTable->setText(XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) ) );
    ui->discount->setText(XmlManipulation::getData(g.getTagName(g.Discount),g.getattribute(g.Discount)));
}

void AdminWidget::deleteVecterData()
{
    for (int i = 0; i < itemlist.count(); ++i)
    {
        delete itemlist[i];
    }
    itemlist.clear();
    qDebug() << "AdminWidget.cpp (deleteVecterData) : vector data has been deleted";
}

AdminWidget::~AdminWidget()
{
    this->deleteVecterData();
    delete ui;
}

void AdminWidget::on_AddItem_clicked()
{
    addItem add;
    add.exec() ;
    this->loadData();
}

void AdminWidget::on_editButton_clicked()
{
    EditTableNoAndDiscount e;
    e.exec();
    this->loadInfo();
}

void AdminWidget::on_SearchButton_clicked()
{
    QString columnName;
    QString cmd;
    QString searchText = ui->SearchTextBox->text();
    bool isPrice = false, isName = false, isAll = false;

    if(!ui->SearchTextBox->text().isEmpty())
    {
        if(ui->menuColumn->currentText() == ui->menuColumn->itemText(0))
        {
            isAll = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(1))
        {
            columnName = "id";
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(2))
        {
            columnName = "itemName";
            isName = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(3))
        {
            columnName = "category";
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(4))
        {
            columnName = "Price";
            isPrice = true;
        }

        if(isPrice)
        {
            cmd = "SELECT * FROM tblMenu WHERE "+ columnName +" = "+ searchText +" ORDER BY id" ;
        }
        else if(isName)
        {
            cmd = "SELECT * FROM tblMenu WHERE "+ columnName +" LIKE '%"+ searchText +"%' ORDER BY id" ;
        }
        else if(isAll)
        {
            cmd = "SELECT * FROM tblMenu WHERE id = '"+searchText+"' OR itemName LIKE '%"+ searchText +"%' OR category LIKE '%"+ searchText +"%' OR Price = '"+ searchText +"' ORDER BY id" ;
        }
        else
        {
            cmd = "SELECT * FROM tblMenu WHERE "+ columnName +" LIKE '%"+ ui->SearchTextBox->text() +"%' ORDER BY id" ;
        }

    }
    else
    {
        cmd = "SELECT * FROM tblMenu ORDER BY id";
    }

    this->deleteVecterData();
    databaseCon d;
    QSqlQuery* q = d.execute(cmd);
    while( q->next() )
    {
        ItemWidget *item = new ItemWidget(this);
        itemlist.push_back(item);
        item->setData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString());
        ui->itemListContainer->addWidget(item);
    }
    delete q;
}

void AdminWidget::on_SearchTextBox_returnPressed()
{
    emit on_SearchButton_clicked();
}

void AdminWidget::on_SearchTextBox_textChanged(const QString &arg1)
{
    qDebug() << "AdminWidget.cpp (on_SearchTextBox_textChanged) : text changed : " <<arg1;
    emit on_SearchButton_clicked();
}

void AdminWidget::on_btnEditCategory_clicked()
{
    EditCategory e(this);
    e.exec();
}
