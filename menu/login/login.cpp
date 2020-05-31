#include "login.h"
#include "ui_login.h"
#include "dyner.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    myParent = parent;

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(true)
    {
        static_cast<Dyner*>(myParent)->homeWidget();
    }
}
