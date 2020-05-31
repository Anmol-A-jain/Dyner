#include "report.h"
#include "ui_report.h"

#include "data/globaldata.h"

report::report(int srNo,QString staffId,QString userName,QString desig,QString date,QString module,QString entry,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::report)
{
    ui->setupUi(this);

    ui->lblSrNo->setText(QString::number(srNo));
    ui->lblId->setText(staffId);
    ui->lblName->setText(userName);
    ui->lblmodule->setText(module);
    ui->lblentry->setText(entry);
   // ui->lblexit->setText(exit);
    ui->lbldate->setText(date);
    ui->lblDesig->setText(desig);

    GlobalData::setShadow(this);

}

report::~report()
{
    delete ui;
}
