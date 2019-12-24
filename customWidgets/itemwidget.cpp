#include "itemwidget.h"
#include "ui_itemwidget.h"

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    ui->setupUi(this);

    ui->deletebtn->setText(QString("\U0001F5D1"));

    ui->editbtn->setText(QString("\U0001F58A"));
}

void ItemWidget::setData(QString id, QString name, QString category, QString price)
{
    ui->ItemId->setText(id);
    ui->name->setText(name);
    ui->Categoty->setText(category);
    ui->Price->setText(price);
}

ItemWidget::~ItemWidget()
{
    delete ui;
}

