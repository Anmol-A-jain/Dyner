#include "report.h"
#include "ui_report.h"

report::report(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::report)
{
    ui->setupUi(this);
}

report::~report()
{
    delete ui;
}
