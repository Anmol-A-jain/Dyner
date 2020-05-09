#include "editstaff.h"
#include "ui_editstaff.h"

#include "../staff.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "data/databasecon.h"

editStaff::editStaff(QString id,QString name,QString username,QString designation,double salary,QString mblno,QString address,QString city ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editStaff)
{
    ui->setupUi(this);

    this->myParent = parent;

    ui->txtId->setText(id);
    ui->txtName->setText(name);
    ui->txtuser->setText(username);
    ui->txtDesig->addItem(designation);
    ui->sal->setNum(salary);
    ui->txtmbl->setText(mblno);
    ui->txtaddress->setText(address);
    ui->txtcity->setText(city);

    databaseCon d;
  //  QString desig = ui->txtDesig->currentText();
    QString cmd = "SELECT designation,salary FROM tblDesignation ORDER BY designation" ;
    //where designation = '"+desig+"'
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        QString data =q->value("designation").toString();

        if(data != designation)
        {
            ui->txtDesig->addItem(data);
        }
    }

    delete q;
}

editStaff::~editStaff()
{
    delete ui;
}

void editStaff::on_btnUpdate_clicked()
{
    databaseCon d;

   QString id =  ui->txtId->text();
   QString name =  ui->txtName->text();
   QString username =  ui->txtuser->text();
   QString designation =  ui->txtDesig->currentText();
   QString salary = ui->sal->text();
   QString mbl =  ui->txtmbl->text();
   QString address =  ui->txtaddress->text();
   QString city =  ui->txtcity->text();


    if(!id.isEmpty() && !name.isEmpty() && !username.isEmpty() && !designation.isEmpty() && !mbl.isEmpty() && !address.isEmpty() && !city.isEmpty() )
    {
        QString cmd = "UPDATE mstTblStaff SET name = '"+name+"',address = '"+address+"' ,city = '"+city+"',mbl_no = '"+mbl+"', designation = '"+designation+"' , username = '"+username + "' where staff_id = '"+id+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;
        static_cast<staff*>(myParent)->loadData();
        QMessageBox::information(this,"Information","Employee Data Has Been Updated");
        emit this->accept();
    }
    else
    {
        QString errormsg = "Following Fields are empty : \n";
        if(id.isEmpty())
        {
            errormsg.append("\nPlease enter Id");
        }

        if(name.isEmpty())
        {
            errormsg.append("\nPlease enter Name");
        }

        if(designation.isEmpty())
        {
            errormsg.append("\nPlease enter Desigantion");
        }
        if(username.isEmpty())
        {
            errormsg.append("\nPlease enter UserName");
        }
        if(mbl.isEmpty())
        {
            errormsg.append("\nPlease enter Mobile Number");
        }
        if(address.isEmpty())
        {
            errormsg.append("\nPlease enter Address");
        }
        if(city.isEmpty())
        {
            errormsg.append("\nPlease enter City");
        }

        QMessageBox::critical(this,"Error",errormsg);
    }
}

void editStaff::on_txtDesig_currentIndexChanged(const QString &arg1)
{

    databaseCon d;
    QString cmd ;

    cmd = "SELECT salary FROM tblDesignation where designation = '" +arg1+"' " ;

    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        QString salary = q->value("salary").toString();
        ui->sal->setText(salary);
    }
}
