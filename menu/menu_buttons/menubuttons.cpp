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
    this->setShadow(ui->btnStaff,color);

    this->parentName = parent;

    if(!GlobalData::isAdmin)
    {
        ui->btnAdmin->hide();
        ui->btnStaff->hide();
    }
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

void MenuButtons::on_btnStaff_clicked()
{
    static_cast<Dyner*>(parentName)->staffButtonClick();
}

void MenuButtons::setShadow(QWidget *widget, QColor color)
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(.0);
    effect->setBlurRadius(30.0);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}

