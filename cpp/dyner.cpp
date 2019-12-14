#include <QDebug>
#include "header/dyner.h"
#include "header/menubuttons.h"
#include "ui_dyner.h"

Dyner::Dyner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dyner)
{

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    ui->menuList->hide();
    isMenuHidden = true;
    menuWidget = new menuButtons(this);
    childFrame = menuWidget;
    ui->windowContainer->addWidget(childFrame);


}

Dyner::~Dyner()
{
    delete childFrame;
    delete ui;
}

Ui::Dyner* Dyner::getUi()
{
    return ui;
}

QHBoxLayout *Dyner::getFrame()
{
    return ui->windowContainer;
}

QWidget *Dyner::newFrame(int option)
{
    /*
     * 0. oreder
     * 1. bill history
     * 2. bill req
     * 3. admin
     * */

    switch (option)
    {
        case 0 :
        {
            return new menuButtons(this);
        }
        case 1 :
        {
            return new OrderWidget;
        }

        case 2 :
        {
            return new BillHistoryWidget;
        }

        case 3 :
        {
            return new BillReqWidget;
        }

        case 4 :
        {
            return new AdminWidget;
        }
    }
    return childFrame;

}

void Dyner::showMenuAndDeleteThis(int option)
{
    delete childFrame;
    childFrame = newFrame(option);
    ui->windowContainer->addWidget( childFrame );
}

void Dyner::orderButtonClick()
{
    emit on_parentButtonOrder_clicked();
}

void Dyner::billHistoryButtonClick()
{
    emit on_parentButtonBillHistory_clicked();
}

void Dyner::billReqButtonClick()
{
    emit on_parentButtonBillRequest_clicked();
}

void Dyner::adminButtonClick()
{
    emit on_parentButtonAdmin_clicked();
}

void Dyner::on_parentButtonHome_clicked()
{
    showMenuAndDeleteThis(buttonName::home);
    isMenuHidden = true;
    ui->menuList->hide();
}

void Dyner::on_parentButtonOrder_clicked()
{
    showMenuAndDeleteThis(buttonName::order);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }
}


void Dyner::on_parentButtonBillHistory_clicked()
{
    showMenuAndDeleteThis(buttonName::billHistory);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }
}

void Dyner::on_parentButtonBillRequest_clicked()
{
    showMenuAndDeleteThis(buttonName::billReq);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }
}

void Dyner::on_parentButtonAdmin_clicked()
{
    showMenuAndDeleteThis(buttonName::admin);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }
}

void Dyner::on_menuButton_clicked()
{
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }
    else
    {
        isMenuHidden = true;
        ui->menuList->hide();
    }
}

