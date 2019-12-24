#include "header/menu/adminwidget.h"
#include "ui_adminwidget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);

    ItemWidget *i = new ItemWidget;
    i->setData("ID","name","category","price");
    ui->verticalLayout_4->addWidget(i);
    ItemWidget *i1 = new ItemWidget;
    i1->setData("ID","name","category","price");
    ui->verticalLayout_4->addWidget(i1);
    ItemWidget *i2 = new ItemWidget;
    i2->setData("ID","name","category","price");
    ui->verticalLayout_4->addWidget(i2);
}

AdminWidget::~AdminWidget()
{
    delete ui;
}
