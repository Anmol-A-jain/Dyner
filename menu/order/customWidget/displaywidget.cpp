#include "displaywidget.h"
#include "ui_displaywidget.h"

displayWidget::displayWidget(QString id,QString name, QString category, int Qty, double rate ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::displayWidget)
{
    ui->setupUi(this);

    ui->lblId->setText(id);
    ui->lblName->setText(name);
    ui->lblCategory->setText(category);
    ui->doubleSpinBox->setValue(Qty);
    ui->lblRate->setText(QString::number(rate));
}

displayWidget::~displayWidget()
{
    delete ui;
}
