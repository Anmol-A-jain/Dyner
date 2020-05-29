#include "login.h"
#include "ui_login.h"

#include <data/databasecon.h>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_btnlogin_clicked()
{
    QString id = ui->txtid->text();
    QString name = ui->txtuser->text();

    if(!id.isEmpty() && !name.isEmpty())
    {
        databaseCon d;
        QString cmd = "select staff_id, username from mstTblStaff where staff_id = '"+id+"' AND  username = '"+name+"' AND designation = 'manager' " ;
        QSqlQuery* q = d.execute(cmd);
        qDebug() << d.execute(cmd);

        if(d.execute(cmd))
        {
           int count=0;
            while(q->next())
            {
                count++;
            }
            if(count == 1)
            {
                QMessageBox::information(this,"Login successfully","Username "+name+" has been done");
                QString entry = QTime::currentTime().toString("HH:mm:ss");
                QString c_date = QDate::currentDate().toString("d-MM-yyyy");
                QString cmd1 = "INSERT INTO tblLogin (S_id,entry,module_name,date) VALUES('" + id + "','" + entry + "','admin','" + c_date + "')" ;
                q = d.execute(cmd1);
                delete q;
                emit this->accept();
            }

           else if(count < 1)
           {
               QMessageBox::critical(this,"STOP","You have no right to access it");
           }
        }
        else
        {
            qDebug()<<  "query no execute";
        }

        delete q;
    }
    else
    {
        QString errormsg = "Following Fields are emply : \n";
        if(id.isEmpty())
        {
            errormsg.append("\nPlease enter Id");
        }

        if(name.isEmpty())
        {
            errormsg.append("\nPlease enter UserName");
        }
        QMessageBox::critical(this,"Error",errormsg);
    }

}
