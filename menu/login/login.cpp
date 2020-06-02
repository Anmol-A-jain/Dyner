#include <QMessageBox>

#include "login.h"
#include "ui_login.h"
#include "dyner.h"
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include "DialogBox/changepassword.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    myParent = parent;
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QString name = ui->txtName->text();
    QString pass = ui->txtPass->text();

    GlobalData g;
    QString adminPass = XmlManipulation::getData(g.getTagName(g.loginData),g.getattribute(g.loginData) );

    bool isvalid = ( (name == "admin") && (pass == adminPass) );

    bool isMasterPaswword = ( (name == "admin") && (pass == "welcome@dyner") );

    if(isvalid || isMasterPaswword)
    {
        GlobalData::isAdmin = true;
        static_cast<Dyner*>(myParent)->homeWidget();
    }
    else
    {
        QMessageBox::critical(this,"Login Failed","Your login Passowrd or Username is wrong");
    }
}

void Login::on_txtName_returnPressed()
{
    on_btnLogin_clicked();
}

void Login::on_txtPass_returnPressed()
{
    on_btnLogin_clicked();
}

void Login::on_btnSkip_clicked()
{
    GlobalData::isAdmin = false;
    static_cast<Dyner*>(myParent)->homeWidget();
}

void Login::on_btnChangePass_clicked()
{
    ChangePassword c(true);
    c.exec();
}
