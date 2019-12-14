#include "header/menubuttons.h"
#include "ui_menubuttons.h"
#include "ui_dyner.h"
#include "header/dyner.h"

menuButtons::menuButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuButtons)
{
    ui->setupUi(this);

    this->setShadow(ui->btnAdmin,QColor(0,160,250));
    this->setShadow(ui->btnOrder,QColor(0,160,250));
    this->setShadow(ui->btnBillReq,QColor(0,160,250));
    this->setShadow(ui->btnBillHistory,QColor(0,160,250));


    //auto myParent = static_cast<Dyner*>(parent) ;

    this->parentName = parent;

}

menuButtons::~menuButtons()
{
    delete ui;
}

void menuButtons::setShadow(QWidget *widget, QColor color)
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(0.0);
    effect->setBlurRadius(30.0);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}



void menuButtons::on_btnOrder_clicked()
{
    static_cast<Dyner*>(parentName)->orderButtonClick();
}

void menuButtons::on_btnBillHistory_clicked()
{
    static_cast<Dyner*>(parentName)->billHistoryButtonClick();
}

void menuButtons::on_btnBillReq_clicked()
{
    static_cast<Dyner*>(parentName)->billReqButtonClick();
}

void menuButtons::on_btnAdmin_clicked()
{
    static_cast<Dyner*>(parentName)->adminButtonClick();
}
