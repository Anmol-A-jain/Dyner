#include "dyner.h"

#include "menu/menu_buttons/menubuttons.h"
#include "menu/admin/adminwidget.h"
#include "menu/bill_history/billhistorywidget.h"
#include "menu/order/orderwidget.h"

#include "data/databasecon.h"
#include "data/xmlmanipulation.h"

#include "ui_dyner.h"
#include <QDebug>
#include <QtXml>

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
    server.startServer();

}

Dyner::~Dyner()
{
    //deleting all pointer
    server.closeAllConnection();
    delete currentShaddowEffect;
    delete childFrame;
    delete ui;
}

Ui::Dyner* Dyner::getUi()
{
    //returning ui object for this class
    return ui;
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
        case buttonName::home :
        {
            return new MenuButtons(this);
        }
        case buttonName::order :
        {
            return new OrderWidget;
        }

        case buttonName::billHistory :
        {
            return new BillHistoryWidget;
        }

        case buttonName::admin :
        {
            return new AdminWidget;
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
    delete deleteItLater;
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
