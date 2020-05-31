#include "menubuttons.h"
#include "ui_menubuttons.h"
#include "dyner.h"

MenuButtons::MenuButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuButtons)
{
    ui->setupUi(this);

    // setting shadow to all buttons
    QColor color(0,0,0);
    this->setShadow(ui->btnAdmin,color);
    this->setShadow(ui->btnOrder,color);
    this->setShadow(ui->btnBillHistory,color);
    this->setShadow(ui->btnServer,color);
<<<<<<< HEAD
=======
    this->setShadow(ui->btnStaff,color);
    this->setShadow(ui->btnlogin,color);
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6

    this->parentName = parent;
}

MenuButtons::~MenuButtons()
{
    delete ui;
}

void MenuButtons::on_btnOrder_clicked()
{
    static_cast<Dyner*>(parentName)->orderButtonClick();
}

void MenuButtons::on_btnBillHistory_clicked()
{
    static_cast<Dyner*>(parentName)->billHistoryButtonClick();
}

void MenuButtons::on_btnAdmin_clicked()
{
    static_cast<Dyner*>(parentName)->adminButtonClick();
}

void MenuButtons::on_btnServer_clicked()
{
    static_cast<Dyner*>(parentName)->serverButtonClick();
}

void MenuButtons::setShadow(QWidget *widget, QColor color)
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(.0);
    effect->setBlurRadius(30.0);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}
<<<<<<< HEAD
=======

void MenuButtons::on_btnStaff_clicked()
{
    static_cast<Dyner*>(parentName)->staffButtonClick();
}


void MenuButtons::on_btnlogin_clicked()
{
    static_cast<Dyner*>(parentName)->loginReportClick();
}
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
