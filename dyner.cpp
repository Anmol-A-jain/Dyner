#include "dyner.h"

#include "menu/menu_buttons/menubuttons.h"
#include "menu/admin/adminwidget.h"
#include "menu/bill_history/billhistorywidget.h"
#include "menu/order/orderwidget.h"
#include "menu/ServerManagement/servermanagement.h"
<<<<<<< HEAD
=======
#include "menu/staff/staff.h"
#include "login/reportlogin/loginreport.h"
#include "login/login.h"

//#include "menu/admin/login/login.h"
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6

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

<<<<<<< HEAD
=======
    login log;



    log.exec();

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
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
<<<<<<< HEAD
     * 2. bill req
     * 3. admin
     * 4. server management
     * */

=======
     * 2. admin
     * 3. server management
     * 4. staff management
     * 5. login report
     * */


>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
    switch (option)
    {
        case buttonName::home :
        {
            menuWindow = new MenuButtons(this);
            return menuWindow;
<<<<<<< HEAD
=======

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
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
<<<<<<< HEAD
    }
    return childFrame;
=======
        case buttonName::Staff :
        {

            staffWindow = new staff(this);
            return staffWindow;
        }
        case buttonName::L_Report :
        {
            l_reportWindow = new LoginReport(this);
            return l_reportWindow;
        }
    }
    return childFrame;

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
}

void Dyner::loadWidgetWindow(int option)
{
<<<<<<< HEAD
    childFrame->deleteLater();
    childFrame = newFrame(option);
    ui->windowContainer->addWidget( childFrame );
=======


    childFrame->deleteLater();
    childFrame = newFrame(option);
    ui->windowContainer->addWidget( childFrame );

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
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

<<<<<<< HEAD
=======
void Dyner::staffButtonClick()
{
    emit on_parentButtonStaff_clicked();
}

void Dyner::loginReportClick()
{
    emit on_parentButtonlogin_clicked();
}


>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
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
<<<<<<< HEAD
=======

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
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

<<<<<<< HEAD
=======
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

void Dyner::on_parentButtonlogin_clicked()
{
    loadWidgetWindow(buttonName::L_Report);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonlogin;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");
}


>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
DynerServer *Dyner::getServer()
{
    return server;
}
<<<<<<< HEAD
=======


>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
