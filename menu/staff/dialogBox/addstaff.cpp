#include "addstaff.h"
#include "ui_addstaff.h"

#include "../staff.h"
#include <data/databasecon.h>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QKeyEvent>

addStaff::addStaff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStaff)
{
    ui->setupUi(this);

      int size = ui->designation->height() - 5 ;

      ui->btnaddDesignation->setMinimumSize(size,size);
      ui->btnaddDesignation->setMaximumSize(size,size);

      this->LoadDesignation();

    databaseCon d;
    QString cmd = "SELECT staff_id FROM mstTblStaff ORDER BY staff_id" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        QString str = q->value("staff_id").toString();
        int len = str.length(), i = 0;

        for(QChar &ch : str )
        {
            ++i;
            if(i == len)
            {
                if(ch == '9')
                {
                    ch = '0';
                }
                else
                {
                    ch = ch.unicode() + 1;
                }
            }
        }

        ui->id->setText(str);
    }
    delete q;


    myParent = parent;

    if(myParent)
    {
        if(ui->designation->count() == 0)
        {
            QMessageBox::warning(this,"Warning","<h3>Empty designation List</h3>\nThere is no designation available. please enter at least one designation");
            static_cast<staff *>(myParent)->btnAddDesignationClicked();
            this->LoadDesignation();
        }

        cmd = "SELECT designation,salary FROM tblDesignation ORDER BY designation" ;
        q = d.execute(cmd);

        if(q->size() == 0)
        {
            QMessageBox::warning(this,"Warning","<h3>Empty designation List</h3>\nYou have not add any data in designation.");

            QKeyEvent *event = new QKeyEvent( QEvent::KeyPress, Qt::Key_Escape ,Qt::NoModifier);
            QCoreApplication::postEvent (this, event);
        }
    }

    delete q;
}

addStaff::~addStaff()
{
    delete ui;
}
void addStaff::LoadDesignation()
{
    ui->designation->clear();
    databaseCon d;
   // QString desig = ui->designation->currentText();
    QString cmd = "SELECT designation,salary FROM tblDesignation  WHERE designation LIKE '%"+ui->designation->currentText()+"%' ORDER BY designation" ;
    // where designation = '"+desig+"'
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        ui->designation->addItem(q->value("designation").toString());
        //ui->salary->setText(q->value("salary").toString());
    }
    delete q;
}


void addStaff::on_btnadd_clicked()
{
    databaseCon d;

    QString id = ui->id->text();

    QString cmd = "SELECT * FROM mstTblStaff WHERE staff_id = '"+id+"' " ;

    QSqlQuery* q = d.execute(cmd);
    while (q->next())
    {
        QMessageBox::warning(this,"Error","Staff Id : "+id+" is already assign to \""+q->value("name").toString()+"\"\n Designation : "+q->value("designation").toString()+"\n UserName : "+q->value("username").toString()+"");
        return;
    }
    delete q;

    QString name = ui->name->text();
    QString username = ui->usename->text();
    QString designation = ui->designation->currentText();
    QString salary = ui->salary->text();
    QString mbl = ui->mblNo->text();
    QString address = ui->address->text();
    QString city = ui->city->text();



    if(!id.isEmpty() && !name.isEmpty() && !username.isEmpty() && !designation.isEmpty() && !mbl.isEmpty() && !address.isEmpty() && !city.isEmpty() )
    {
        cmd = "INSERT INTO mstTblStaff VALUES('" + id + "','" + name + "','" + address + "','" + city + "','" + mbl + "','" + designation + "','" + username + "')" ;
        q = d.execute(cmd);
        delete q;

        QMessageBox::information(this,"Employee Added","Emp "+ name +",\n Username  "+ username +" has been added");
        this->accept();
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

void addStaff::on_btnaddDesignation_clicked()
{
    static_cast<staff*>(myParent)->btnAddDesignationClicked();
    this->LoadDesignation();
}

void addStaff::on_designation_currentIndexChanged(const QString &arg1)
{
    databaseCon d;
    QString cmd ;

    cmd = "SELECT salary FROM tblDesignation where designation = '" +arg1+"' " ;

    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        QString salary = q->value("salary").toString();
        ui->salary->setText(salary);
    }
}

void addStaff::on_name_textChanged(const QString &arg1)
{
    ui->usename->setText(ui->name->text().append("@Dyner"));
}
