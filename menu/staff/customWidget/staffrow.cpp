#include "staffrow.h"
#include "ui_staffrow.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include <QMessageBox>
#include "menu/staff/staff.h"

StaffRow::StaffRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffRow),
    isEditModeOn(false)
{
    ui->setupUi(this);
    myParent = parent;

    // adding unicode icon to delete and edit buttons
    ui->deletebtn->setText(QString("\U0001F5D1"));
    ui->editbtn->setText(QString("\U0001F58A"));

    GlobalData::setShadow(this);
    GlobalData::setShadow(ui->txtName);
    GlobalData::setShadow(ui->List);
    GlobalData::setShadow(ui->txtUsername);

    ui->txtName->hide();
    ui->txtUsername->hide();
    ui->List->hide();
}

StaffRow::~StaffRow()
{
    delete ui;
}

void StaffRow::setData(QString ID, QString name, QString designation, QString password,QString username)
{
    ui->ID->setText(ID);
    ui->name->setText(name);
    ui->designation->setText(designation);
    ui->password->setText(password);
    ui->username->setText(username);
}

void StaffRow::on_showPass_clicked()
{
    QLineEdit::EchoMode echoMode = ui->password->echoMode();
    if(echoMode == QLineEdit::Password)
    {
        ui->password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->password->setEchoMode(QLineEdit::Password);
    }
}

void StaffRow::on_editbtn_clicked()
{
    if(isEditModeOn == false)
    {
        isEditModeOn = true;

        ui->txtName->show();
        ui->List->show();
        ui->txtUsername->show();

        ui->name->hide();
        ui->designation->hide();
        ui->username->hide();

        ui->txtName->setText(ui->name->text());
        ui->txtUsername->setText(ui->username->text());

        int index = ui->List->findText(ui->designation->text());
        ui->List->setCurrentIndex(index);

        ui->password->setReadOnly(false);
        GlobalData::setShadow(ui->passwordContainer);

        ui->editbtn->setText(QString("\U00002713"));
    }
    else
    {
        isEditModeOn = false;

        ui->txtName->hide();
        ui->List->hide();
        ui->txtUsername->hide();

        ui->name->show();
        ui->designation->show();
        ui->username->show();

        ui->name->setText(ui->txtName->text());
        ui->username->setText(ui->txtUsername->text());

        ui->designation->setText(ui->List->currentText());

        ui->password->setReadOnly(false);
        ui->passwordContainer->setGraphicsEffect(nullptr);

        ui->editbtn->setText(QString("\U0001F58A"));

        databaseCon d;
        QString cmd;

        cmd = "UPDATE tblStaff SET name = '"+ui->name->text()+"',designation = '"+ui->designation->text()+"',password = '"+ui->password->text()+"',username = '"+ui->username->text()+"' WHERE ID = '"+ui->ID->text()+"';";
        delete d.execute(cmd);

        QLineEdit::EchoMode echoMode = ui->password->echoMode();
        if(echoMode == QLineEdit::Normal)
        {
            on_showPass_clicked();
        }
    }
}

void StaffRow::on_deletebtn_clicked()
{
    QMessageBox::StandardButton btn =  QMessageBox::warning(this,"Delete","Do you want to delete this Staff Information",QMessageBox::No|QMessageBox::Yes,QMessageBox::No);

    if(btn == QMessageBox::No)
    {
        return;
    }

    databaseCon d;
    QString cmd;

    cmd = "DELETE FROM tblStaff WHERE ID = '"+ui->ID->text()+"';";
    delete d.execute(cmd);

    static_cast<Staff*>(myParent)->loadData();
}
