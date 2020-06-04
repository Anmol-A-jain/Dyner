#include "addstaff.h"
#include "ui_addstaff.h"
#include "data/databasecon.h"
#include <QMessageBox>

addStaff::addStaff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStaff)
{
    ui->setupUi(this);
    myParent = parent;
}

addStaff::~addStaff()
{
    delete ui;
}

void addStaff::on_btnAdd_clicked()
{
    QString ID = ui->txtId->text();
    QString name = ui->txtName->text();
    QString designation = ui->List->currentText();
    QString password = ui->txtPassword->text();
    QString username = ui->txtUsername->text();

    bool ifNotValid = ID.isEmpty() || name.isEmpty() || designation.isEmpty() || password.isEmpty() || username.isEmpty();

    if(ifNotValid)
    {
        QMessageBox::information(this,"Fill all data","One or more fields are empty");
        return;
    }

    databaseCon d;
    QString cmd;

    cmd = "SELECT ID FROM tblStaff WHERE ID='"+ID+"';";
    QSqlQuery* q = d.execute(cmd);
    int count = 0;

    while(q->next())
    {
        count++;
    }
    delete q;

    cmd = "SELECT ID FROM tblStaff WHERE username='"+username+"';";
    q = d.execute(cmd);
    int userCount = 0;

    while(q->next())
    {
        userCount++;
    }

    QString errMsg ;
    errMsg = (count != 0)? "ID: "+ID+" is not available\n" : "";
    errMsg = (userCount != 0)? "Username: "+username+" is not available" : "";

    if(errMsg != "")
    {
        QMessageBox::information(this,"Not valid",errMsg);
        return;
    }

    cmd = "INSERT INTO tblStaff VALUES('"+ID+"','"+name+"','"+designation+"','"+password+"','"+username+"');";
    delete d.execute(cmd);

    accept();

}

void addStaff::on_buttonBox_rejected()
{
    reject();
}
