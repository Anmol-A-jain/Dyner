#include "dyner.h"

#include "menu/menu_buttons/menubuttons.h"
#include "menu/admin/adminwidget.h"
#include "menu/bill_history/billhistorywidget.h"
#include "menu/order/orderwidget.h"
#include "menu/ServerManagement/servermanagement.h"
#include "menu/staff/staff.h"

//#include "menu/admin/login/login.h"

#include "data/databasecon.h"
#include "data/xmlmanipulation.h"

#include "ui_dyner.h"
#include <QDebug>
#include <QtXml>
#include <QCloseEvent>

DynerServer* Dyner::server;
QWidget* Dyner::childFrame;

Dyner::Dyner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dyner)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    //hiding menu list and setting menuButton to window container
    ui->menuList->hide();
    isMenuHidden = true;
    QWidget* menuButtons  = new MenuButtons(this);
    childFrame = menuButtons;
    ui->windowContainer->addWidget(childFrame);

    //setting shadow to homeButton in ui
    currentShaddowEffect = ui->parentButtonHome;
    this->setShadow(currentShaddowEffect,QColor(150,75,0)); //calling UDF

    // removing alpha color from ui->horizontalFrame for first time load
    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;}");

    databaseCon::initDB();

    // starting TCP server
    server = new DynerServer(this);
    server->startServer();

}

Dyner::~Dyner()
{
    //deleting all pointer
    delete currentShaddowEffect;
    delete childFrame;
    delete ui;
}

QWidget *Dyner::newFrame(int option)
{
    /*
     * 0. oreder
     * 1. bill history
     * 2. admin
     * 3. server management
     * 4. staff management
     * */

    switch (option)
    {
        case buttonName::home :
        {
            menuWindow = new MenuButtons(this);
            return menuWindow;
        }
        case buttonName::order :
        {
            orderWindow = new OrderWidget(this);
            return orderWindow;
        }

        case buttonName::billHistory :
        {
            historyWindow = new BillHistoryWidget(this);
            return historyWindow;
        }

        case buttonName::admin :
        {
            adminWindow = new AdminWidget(this);
            return adminWindow;
        }
        case buttonName::serverManagement :
        {

            serverWindow = new ServerManagement(this);
            return serverWindow;
        }
        case buttonName::Staff :
        {

            staffWindow = new staff(this);
            return staffWindow;
        }
    }
    return childFrame;
}

void Dyner::loadWidgetWindow(int option)
{
    childFrame->deleteLater();
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

void Dyner::adminButtonClick()
{
    emit on_parentButtonAdmin_clicked();
}

void Dyner::serverButtonClick()
{
    emit on_parentButtonManagement_clicked();
}

void Dyner::staffButtonClick()
{
    emit on_parentButtonStaff_clicked();
}


void Dyner::setShadow(QWidget *widget, QColor color)
{
    auto deleteItLater = currentShaddowEffect->graphicsEffect() ;

    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(3.0);
    effect->setBlurRadius(10.0);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
    currentShaddowEffect = static_cast<QPushButton*>(widget);

    ui->widgetTitle->setText(static_cast<QPushButton*>(widget)->text());
    ui->widgetTitle->setFont(QFont("Arial", 20));
    deleteItLater->deleteLater();
}

void Dyner::closeEvent(QCloseEvent *event)
{
    DynerServer::closeAllConnection();
    event->accept();
}

void Dyner::sendToDataKitchen(qint16 orderNo, qint16 tblNo, QString name)
{
    server->sendToKitchren(orderNo,tblNo,name);
}

void Dyner::serverSideAddItem()
{
    if(childFrame == serverWindow) static_cast<ServerManagement*>(serverWindow)->loadData();
}

void Dyner::on_parentButtonHome_clicked()
{
    loadWidgetWindow(buttonName::home);
    isMenuHidden = true;
    ui->menuList->hide();

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonHome;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: }");

}

void Dyner::on_parentButtonOrder_clicked()
{
    loadWidgetWindow(buttonName::order);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonOrder;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");

}


void Dyner::on_parentButtonBillHistory_clicked()
{
    loadWidgetWindow(buttonName::billHistory);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonBillHistory;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");

}

void Dyner::on_parentButtonAdmin_clicked()
{
    loadWidgetWindow(buttonName::admin);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonAdmin;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");

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

void Dyner::on_parentButtonManagement_clicked()
{
    loadWidgetWindow(buttonName::serverManagement);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonManagement;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");
}

void Dyner::on_parentButtonStaff_clicked()
{
    loadWidgetWindow(buttonName::Staff);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonStaff;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");
}


DynerServer *Dyner::getServer()
{
    return server;
}

