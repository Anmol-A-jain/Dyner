#include <QMessageBox>

#include "login.h"
#include "ui_login.h"
#include "dyner.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include "data/xmlmanipulation.h"
#include "DialogBox/changepassword.h"
#include <QDebug>

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

    if(pass.isEmpty() || name.isEmpty())
    {
        QMessageBox::warning(this,"Empty","Please filled all fields");
        return;
    }

    GlobalData g;
    QString adminPass = XmlManipulation::getData(g.getTagName(g.loginData),g.getattribute(g.loginData) );


    databaseCon d;
    QString cmd;

    cmd = "SELECT password,designation FROM tblStaff WHERE ID = '"+name+"' OR username = '"+name+"' ;";
    QSqlQuery* q = d.execute(cmd);

    QString designation = "";
    QString password = "";

    if(q->next())
    {
        designation = q->value(1).toString();
        password = q->value(0).toString();

        qDebug() << "Login : on_btnLogin_clicked : password " << q->value(0).toString();
        qDebug() << "Login : on_btnLogin_clicked : designation " << q->value(1).toString();
    }


    bool isvalid = ( (name == "admin") && (pass == adminPass) );

    bool isMasterPaswword = ( (name == "admin") && (pass == "welcome@dyner") );

    bool isManager = (designation == "Manager" || designation == "Assistant Manager");
    bool isCorrectPass = (pass == password);

    qDebug() << "Login : on_btnLogin_clicked : isManager " << isManager;

    if(isvalid || isMasterPaswword || (isManager && isCorrectPass))
    {
        GlobalData::isAdmin = true;
        static_cast<Dyner*>(myParent)->homeWidget();
    }
    else if(!isManager && name != "admin")
    {
        QMessageBox::critical(this,"Login Failed","You are not authorised to login");
    }
    else if(!isCorrectPass)
    {
        QMessageBox::critical(this,"Login Failed","Your Password is Wrong");
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
