#include "addorderitem.h"
#include "ui_addorderitem.h"
#include "customWidgets/order/orderitemdata.h"
#include "data/databasecon.h"
#include <QDebug>

AddOrderItem::AddOrderItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrderItem)
{
    ui->setupUi(this);
    myParent = parent;

    itemList = new QWidget;
    layout = new QVBoxLayout;

    itemList->setLayout(layout);
    //ui->scrollArea->setWidget(itemList);

    this->loadData();

}


AddOrderItem::~AddOrderItem()
{
    delete ui;
    itemList->deleteLater();
    layout->deleteLater();
}

void AddOrderItem::loadData()
{

    this->deleteVecterData();
    databaseCon d;
    QString cmd = "select * from tblMenu order by id" ;
    QSqlQuery* q = d.execute(cmd);

    qDebug() << "AddOrderItem.cpp (loadData) : data size" << q->size() ;
    while( q->next())
    {
        OrderItemData *item = new OrderItemData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString(),myParent);
        itemlist.push_back(item);
        ui->displayAddOrder->addWidget(item);
    }

    delete q;
}

void AddOrderItem::deleteVecterData()
{
    for (int i = 0; i < itemlist.count(); ++i)
    {
        delete itemlist[i];
    }
    itemlist.clear();
    qDebug() << "AddOrderItem.cpp (deleteVecterData) : vector data has been deleted";
}
