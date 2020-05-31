#include "loginreport.h"
#include "ui_loginreport.h"

#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

LoginReport::LoginReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginReport)
{
    ui->setupUi(this);
}

LoginReport::~LoginReport()
{
    delete ui;
}
