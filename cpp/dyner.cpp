#include <QDebug>
#include "header/dyner.h"
#include "header/menubuttons.h"
#include "ui_dyner.h"
#include "databasecon.h"
#include <QtXml>

Dyner::Dyner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dyner)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    //hiding menu list and setting menuButton to window container
    ui->menuList->hide();
    isMenuHidden = true;
    QWidget* menuButtons  = new MenuButtons(this);
    childFrame = menuButtons;
    ui->windowContainer->addWidget(childFrame);

    //setting shadow to homeButton in ui
    currentShaddowEffect = ui->parentButtonHome;
    this->setShadow(currentShaddowEffect,QColor(150,75,0)); //calling UDF

    // removing alpha white color from ui->horizontalFrame for first time load
    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;}");


    //Declaring 2 variable which contains PATH of database file and xml file
    QString DBFile = QDir::currentPath() + "/DynerDB.db" ;
    QString xmlFile = QDir::currentPath() + "/init.xml" ;

    // writing database path to XML by colling UDF setXml()
    this->setXml(xmlFile,DBFile);


    qDebug() << "Dyner.cpp : Is file exist :" << QFile::exists(DBFile);

    // copy DB file to hard disk from resource file
    if(!QFile::exists(DBFile))
    {
        QFile::copy(":/DB/database/DynerDB.db",DBFile);
        QFile::setPermissions(DBFile, QFileDevice::ReadOwner|QFileDevice::WriteOwner);
    }
    qDebug() << "Dyner.cpp : DB file location :" << DBFile ;

    // starting TCP server
    server.startServer();

}

Dyner::~Dyner()
{
    //deleting all pointer

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
        case 0 :
        {
            return new MenuButtons(this);
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

void Dyner::setXml(QString xmlFile, QString DBFile)
{
    //Write xml
    QDomDocument document;
    QDomElement root = document.createElement("Dyner");
    document.appendChild(root);
    QDomElement db = document.createElement("Database");
    db.setAttribute("PATH",DBFile);
    root.appendChild(db);

    QFile myfile(xmlFile);
    if(myfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream stream(&myfile);
        stream << document.toString();
        myfile.close();
    }
}

void Dyner::on_parentButtonHome_clicked()
{
    showMenuAndDeleteThis(buttonName::home);
    isMenuHidden = true;
    ui->menuList->hide();

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonHome;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: }");

}

void Dyner::on_parentButtonOrder_clicked()
{
    showMenuAndDeleteThis(buttonName::order);
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
    showMenuAndDeleteThis(buttonName::billHistory);
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

void Dyner::on_parentButtonBillRequest_clicked()
{
    showMenuAndDeleteThis(buttonName::billReq);
    if(isMenuHidden)
    {
        isMenuHidden = false;
        ui->menuList->show();
    }

    currentShaddowEffect->setGraphicsEffect(nullptr);
    currentShaddowEffect = ui->parentButtonBillRequest;
    this->setShadow(currentShaddowEffect,QColor(150,75,0));

    ui->horizontalFrame->setStyleSheet("#horizontalFrame{border-radius : 10px;background-color: rgba(238, 238, 236,0.5);}");

}

void Dyner::on_parentButtonAdmin_clicked()
{
    showMenuAndDeleteThis(buttonName::admin);
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

