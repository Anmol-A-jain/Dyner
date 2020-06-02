#include "changepassword.h"
#include "ui_changepassword.h"
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include <QMessageBox>

ChangePassword::ChangePassword(bool isOldPassrequired, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);

    this->isOldPassrequired = isOldPassrequired;
    if(!isOldPassrequired)
    {
        ui->oldPassContainer->hide();
    }
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_btnLogin_clicked()
{
    QString oldPass = ui->txtPass->text();
    QString newPass = ui->txtNewPass->text();
    QString confirmPass = ui->txtConfirm->text();

    GlobalData g;
    QString adminPass = XmlManipulation::getData(g.getTagName(g.loginData),g.getattribute(g.loginData) );

    if((oldPass != adminPass) && isOldPassrequired )
    {
        QMessageBox::critical(this,"Alert","Old Password is wrong");
    }
    else if(newPass != confirmPass)
    {
        QMessageBox::critical(this,"Alert","New password is not same");
    }
    else
    {
        XmlManipulation::setData(g.getTagName(g.loginData),g.getattribute(g.loginData),newPass);
        QMessageBox::information(this,"Changed","Your password has been changed");

        accept();
    }
}
