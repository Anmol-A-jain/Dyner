#include "loginreport.h"
#include "ui_loginreport.h"

#include <QDate>
#include <QDebug>
#include "data/databasecon.h"



LoginReport::LoginReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginReport)
{
    ui->setupUi(this);

    ui->rdbToday->click();

    ui->deToDate->setDate(QDate::currentDate());
    ui->deFromDate->setDate(QDate::currentDate());
}

LoginReport::~LoginReport()
{
    this->deleteVectorData();
    delete ui;
}

void LoginReport::SelectionChange()
{
    this->deleteVectorData();
    ui->deFromDate->hide();
    ui->deToDate->hide();
    ui->lblTo->hide();
    ui->lblFrom->hide();
    ui->btnSearch->hide();

    databaseCon d;

    QString cmd;

    if(ui->rdbToday->isChecked())
    {
        QString date = QDate::currentDate().toString("d-MM-yyyy");

        cmd = "select l.*,s.username,s.designation from tblLogin l LEFT JOIN mstTblStaff s ON l.S_id = s.staff_id WHERE l.date = '"+date+"' ORDER BY l.date ;" ;
        qDebug() << "loginreport.cpp (SelectionChange) : Today Date : " << date ;
    }
    else if(ui->rdbWeekly->isChecked())
    {
        QDate mDate = QDate::currentDate();
        QDate nDate = mDate.addDays(-7);
        qDebug() << "loginreport.cpp (SelectionChange) : Start Date : " << nDate.toString("d-MM-yyyy") ;

        QString startDate = nDate.toString("yyyy-M-d");
        QString todayDate = mDate.toString("yyyy-M-d");

        cmd = " select l.*,s.username,s.designation from tblLogin l LEFT JOIN mstTblStaff s ON l.S_id = s.staff_id WHERE l.date BETWEEN '"+startDate+"' AND '"+todayDate+"' ORDER BY l.date " ;
        qDebug() << "loginreport.cpp (SelectionChange) : Start Date : " << startDate ;
        qDebug() << "loginreport.cpp (SelectionChange) : Today Date : " << todayDate ;

    }
    else if(ui->rdbFromToDate->isChecked())
    {
        ui->deFromDate->show();
        ui->deToDate->show();
        ui->lblTo->show();
        ui->lblFrom->show();
        ui->btnSearch->show();

        QDate toDate = ui->deToDate->date();
        QDate fromDate = ui->deFromDate->date();

        QString startDate = fromDate.toString("d-MM-yyyy");

        QString todayDate = toDate.toString("d-MM-yyyy");

        cmd = " select l.*,s.username,s.designation from tblLogin l LEFT JOIN mstTblStaff s ON l.S_id = s.staff_id WHERE l.date BETWEEN '"+startDate+"' AND '"+todayDate+"' ORDER BY l.date ;" ;
        qDebug() << "loginreport.cpp (SelectionChange) : Start Date : " << startDate ;
        qDebug() << "loginreport.cpp (SelectionChange) : Today Date : " << todayDate ;
    }

    QSqlQuery* q = d.execute(cmd);

    for(int i = 0;q->next();++i)
    {
        QString staffId = q->value("S_id").toString();
        QString userName = q->value("username").toString();
        QString date = q->value("date").toString();
        QString entry = q->value("entry").toString();
      //  QString exit = q->value("exit_time").toString();
        QString module = q->value("module_name").toString();
        QString desig = q->value("designation").toString();

        report* data = new report(i+1,staffId,userName,desig,date,module,entry,this);
        ui->displayloginrRow->addWidget(data);

        list.push_back(data);
    }
}

void LoginReport::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

void LoginReport::on_rdbToday_clicked()
{
     this->SelectionChange();
}

void LoginReport::on_rdbWeekly_clicked()
{
     this->SelectionChange();
}

void LoginReport::on_rdbFromToDate_clicked()
{
     this->SelectionChange();
}

void LoginReport::on_btnSearch_clicked()
{
     this->SelectionChange();
}
