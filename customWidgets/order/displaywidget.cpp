#include "displaywidget.h"
#include "ui_displaywidget.h"

displayWidget::displayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::displayWidget)
{
    ui->setupUi(this);
}

displayWidget::~displayWidget()
{
    delete ui;
}
