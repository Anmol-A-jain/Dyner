#include "header/menubuttons.h"
#include "ui_menubuttons.h"
#include "ui_dyner.h"
#include "header/dyner.h"

MenuButtons::MenuButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuButtons)
{
    ui->setupUi(this);

    // setting shadow to all buttons
    QColor color(0,0,0);
    this->setShadow(ui->btnAdmin,color);
    this->setShadow(ui->btnOrder,color);
    this->setShadow(ui->btnBillReq,color);
    this->setShadow(ui->btnBillHistory,color);

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

void MenuButtons::on_btnBillReq_clicked()
{
    static_cast<Dyner*>(parentName)->billReqButtonClick();
}

void MenuButtons::on_btnAdmin_clicked()
{
    static_cast<Dyner*>(parentName)->adminButtonClick();
}

void MenuButtons::setShadow(QWidget *widget, QColor color)
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(.0);
    effect->setBlurRadius(30.0);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}
