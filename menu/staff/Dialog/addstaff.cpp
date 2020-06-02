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

    bool ifNotValid = ID.isEmpty() || name.isEmpty() || designation.isEmpty() || password.isEmpty();

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

    if(count)
    {
        QMessageBox::information(this,"ID not valid","ID: "+ID+" is not available");
        return;
    }

    cmd = "INSERT INTO tblStaff VALUES('"+ID+"','"+name+"','"+designation+"','"+password+"');";
    delete d.execute(cmd);

    accept();

}

void addStaff::on_buttonBox_rejected()
{
    reject();
}
