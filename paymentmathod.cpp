#include "paymentmathod.h"
#include "ui_paymentmathod.h"

paymentMathod::paymentMathod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paymentMathod)
{
    ui->setupUi(this);
}

paymentMathod::~paymentMathod()
{
    delete ui;
}
