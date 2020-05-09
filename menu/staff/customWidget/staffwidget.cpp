#include "staffwidget.h"
#include "ui_staffwidget.h"

#include "../staff.h"
#include "menu/staff/dialogBox/editstaff.h"
#include "data/databasecon.h"
#include <QMessageBox>
#include "data/globaldata.h"

staffwidget::staffwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::staffwidget)
{
    ui->setupUi(this);
    this->myParent = parent;

    // adding unicode icon to delete and edit buttons
    ui->deletebtn->setText(QString("\U0001F5D1"));
    ui->editbtn->setText(QString("\U0001F58A"));
    GlobalData::setShadow(this);
}

void staffwidget::setData(QString id,QString name,QString username,QString designation,QString salary,QString mblno,QString address,QString city)
{
   ui->EmpId->setText(id);
   ui->Name->setText(name);
   ui->username->setText(username);
   ui->Designation->setText(designation);
   ui->Salary->setText(salary);
   ui->Mblno->setText(mblno);
   ui->Address->setText(address);
   ui->city->setText(city);

}

staffwidget::~staffwidget()
{
    delete ui;
}

void staffwidget::on_editbtn_clicked()
{
    QString id = ui->EmpId->text() ;
    QString name = ui->Name->text() ;
    QString username = ui->username->text() ;
    QString designation = ui->Designation->text() ;
    double salary = ui->Salary->text().toDouble();
    QString mblno = ui->Mblno->text() ;
    QString address = ui->Address->text() ;
    QString city = ui->city->text() ;


    editStaff e(id,name,username,designation,salary,mblno,address,city,myParent);
    e.exec();
}

void staffwidget::on_deletebtn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Delete", "Do You Want To Delete " + ui->username->text()+ "  Name  " +ui->Name->text() ,QMessageBox::No|QMessageBox::Yes,QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      databaseCon d;

      QString cmd = "DELETE FROM mstTblStaff WHERE staff_id = '"+ ui->EmpId->text() +"'" ;
      QSqlQuery* q = d.execute(cmd);
      if(q != nullptr)
      {
          delete q;
      }
    }
    static_cast<staff*>(myParent)->loadData();
}
