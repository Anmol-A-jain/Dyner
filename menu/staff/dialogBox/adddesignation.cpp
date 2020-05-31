#include "adddesignation.h"
#include "ui_adddesignation.h"

#include "data/databasecon.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include "../staff.h"

addDesignation::addDesignation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDesignation)
{
    ui->setupUi(this);

    this->myParent = parent;

    this->loadData();
}

void addDesignation::loadData()
{
    ui->DesignationList->clear();
    databaseCon d;
 //   QString desig = ui->DesignationList->currentText();
    QString cmd = "SELECT designation,salary FROM tblDesignation ORDER BY designation" ;
    /*where designation =  '"+desig+"*/
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        ui->DesignationList->addItem(q->value("designation").toString());
      //  ui->salaryText->setText(q->value("salary").toString());
    }

    delete q;
}

addDesignation::~addDesignation()
{
    delete ui;
}



void addDesignation::on_search_textChanged(const QString &arg1)
{
    ui->DesignationList->clear();
    databaseCon d;
    QString cmd ;
    if(!ui->searchBox->text().isEmpty())
    {
       cmd = "SELECT designation,salary FROM tblDesignation WHERE designation LIKE '%"+ui->searchBox->text()+"%' ORDER BY designation";
    }
    else
    {
       // QString desig = ui->DesignationList->currentText();
        //where designation =  '"+desig+"'
        cmd = "SELECT designation,salary FROM tblDesignation ORDER BY designation" ;
    }
    QSqlQuery* q = d.execute(cmd);

    qDebug() << "adddesignation.cpp (on_lineEdit_textChanged) : Changed String :" << arg1;
    while(q->next())
    {
        ui->DesignationList->addItem(q->value("designation").toString());
    }

    delete q;
}

void addDesignation::on_DesignationList_currentIndexChanged(const QString &arg1)
{
    ui->designationText->setText(arg1);

    databaseCon d;
    QString cmd ;

    cmd = "SELECT salary FROM tblDesignation where designation = '" +arg1+"' " ;

    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        QString salary = q->value("salary").toString();
        ui->salaryText->setText(salary);
    }
}


void addDesignation::on_add_clicked()
{
    databaseCon d;
    if(!ui->designationText->text().isEmpty())
    {
        bool isContains = false;

        for(int i = ui->DesignationList->count(); i >= 0 ; --i )
        {
            if(ui->DesignationList->itemText(i) == ui->designationText->text())
            {
                isContains = true;
                QMessageBox::critical(this,"Information","Designation already exist");
                return;
            }
        }

        if(!isContains)
        {
            QString cmd = "INSERT INTO tblDesignation VALUES('"+ui->designationText->text()+"',"+ui->salaryText->text()+") ";
            QSqlQuery* q = d.execute(cmd);
            delete q;
            this->loadData();
            QMessageBox::information(this,"Information","Designation has been added");
        }
    }
}

void addDesignation::on_remove_clicked()
{
    int reply = QMessageBox::critical(this,"Delete Whole Designtion","<h3>Do you want to Remove Designation</h3>\nall the staff user this Designation will be get deleted",QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No);
    if(QMessageBox::Yes == reply)
    {
        databaseCon d;
        QString cmd = "DELETE FROM tblDesignation WHERE designation = '"+ ui->DesignationList->currentText() +"'" ;
        QSqlQuery* q = d.execute(cmd);
        delete q;

        static_cast<staff*>(myParent)->loadData();
        this->loadData();
    }
}

void addDesignation::on_update_clicked()
{
    databaseCon d;
    if(!ui->designationText->text().isEmpty())
    {
        QString cmd = "UPDATE tblDesignation SET designation = '"+ui->designationText->text() +"',salary = "+ui->salaryText->text()+" WHERE designation = '"+ui->DesignationList->currentText()+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;

        QMessageBox::information(this,"Information","Designation and Salary has been Updated");
        static_cast<staff*>(myParent)->loadData();
        this->loadData();
    }
}

void addDesignation::on_searchBox_textChanged(const QString &arg1)
{
    ui->DesignationList->clear();
    databaseCon d;
  //  QString desig = ui->DesignationList->currentText();
    QString cmd ;
    if(!ui->searchBox->text().isEmpty())
    {
       cmd = "SELECT designation,salary FROM tblDesignation WHERE designation LIKE '%"+ui->searchBox->text()+"%' ORDER BY designation";
    }
    else
    {
        cmd = "SELECT designation,salary FROM tblDesignation ORDER BY designation" ;
    }
    QSqlQuery* q = d.execute(cmd);

    qDebug() << "addDesignation.cpp (on_lineEdit_textChanged) : Changed String :" << arg1;
    //ui->salaryText->insert(q->value("salary").toString());
    while(q->next())
    {
        ui->DesignationList->addItem(q->value("designation").toString());

    }


    delete q;
}

void addDesignation::on_buttonBox_rejected()
{
    this->reject();
}
