#include "header/menu/adminwidget.h"
#include "ui_adminwidget.h"
#include "customWidgets/itemwidget.h"
#include "DialogBox/additem.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);

    // added some item widget only for testing delete it leter
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

void AdminWidget::on_AddItem_clicked()
{
    addItem add;// = new addItem ;
    add.exec();
}
