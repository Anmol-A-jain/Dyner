#include "header/menu/adminwidget.h"
#include "ui_adminwidget.h"
#include "data/databasecon.h"
#include "DialogBox/additem.h"
#include <QSqlRecord>
#include <QDebug>

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);

    this->loadData();
}

void AdminWidget::loadData()
{
    databaseCon d;
    QString cmd = "select * from tblMenu order by id" ;
    QSqlQuery* q = d.execute(cmd);
    while( q->next())
    {
        ItemWidget *item = new ItemWidget;
        itemlist.push_back(item);
        item->setData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString());
        ui->itemListContainer->addWidget(item);
    }
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
    delete ui;
}

void AdminWidget::on_AddItem_clicked()
{
    addItem add;
    add.exec();

    this->deleteVecterData();
    this->loadData();
}
