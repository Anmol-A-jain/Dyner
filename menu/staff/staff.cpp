#include "staff.h"
#include "ui_staff.h"
#include "menu/staff/Dialog/addstaff.h"
#include "data/databasecon.h"
#include "data/globaldata.h"

#include <QMessageBox>

Staff::Staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);
    myParent = parent;
    this->loadData();

    ui->List->hide();
}

Staff::~Staff()
{
    deleteVectorData();
    delete ui;
}

void Staff::loadData()
{
    deleteVectorData();

    databaseCon d;
    QString cmd;

    cmd = "SELECT * FROM tblStaff ;";
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        StaffRow* row = new StaffRow(this);

        QString ID = q->value(0).toString();
        QString Name = q->value(1).toString();
        QString Designation = q->value(2).toString();
        QString password = q->value(3).toString();
        QString username = q->value(4).toString();

        row->setData(ID,Name,Designation,password,username);
        ui->rowContainer->addWidget(row);
        list.push_back(row);
    }

    delete q;
}

void Staff::deleteVectorData()
{
    for(int i=0; list.count() > i;++i)
    {
        delete list.at(i);
    }
    list.clear();
}

void Staff::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    ui->List->setSizePolicy(ui->SearchTextBox->sizePolicy());
}

void Staff::on_AddStaff_clicked()
{
    addStaff a(this);
    a.exec();
    loadData();
}

void Staff::on_menuColumn_currentIndexChanged(const QString &arg1)
{
    if("Designation" == arg1)
    {
        ui->SearchTextBox->hide();
        ui->List->show();
        on_List_currentIndexChanged(ui->List->currentText());
    }
    else
    {
        ui->SearchTextBox->show();
        ui->List->hide();
    }
}

void Staff::on_SearchTextBox_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        loadData();
        return;
    }

    deleteVectorData();

    databaseCon d;
    QString cmd;

    if(ui->List->currentIndex() == 0)
    {
        cmd = "SELECT * FROM tblStaff WHERE ID LIKE '%"+arg1+"%' OR name LIKE '%"+arg1+"%' OR designation LIKE '%"+arg1+"%' ;";
    }
    else if(ui->List->currentIndex() == 1)
    {
        cmd = "SELECT * FROM tblStaff WHERE ID LIKE '%"+arg1+"%';";
    }
    else if(ui->List->currentIndex() == 2)
    {
        cmd = "SELECT * FROM tblStaff WHERE name LIKE '%"+arg1+"%' ;";
    }
    else
    {

    }

    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        StaffRow* row = new StaffRow(this);

        QString ID = q->value(0).toString();
        QString Name = q->value(1).toString();
        QString Designation = q->value(2).toString();
        QString password = q->value(3).toString();
        QString username = q->value(4).toString();

        row->setData(ID,Name,Designation,password,username);
        ui->rowContainer->addWidget(row);
        list.push_back(row);
    }

    delete q;
}

void Staff::on_List_currentIndexChanged(const QString &arg1)
{
    if(ui->menuColumn->currentIndex() != 3)
    {
        return;
    }

    deleteVectorData();

    databaseCon d;
    QString cmd;

    cmd = "SELECT * FROM tblStaff WHERE designation = '"+arg1+"' ;";

    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        StaffRow* row = new StaffRow(this);

        QString ID = q->value(0).toString();
        QString Name = q->value(1).toString();
        QString Designation = q->value(2).toString();
        QString password = q->value(3).toString();
        QString username = q->value(4).toString();

        row->setData(ID,Name,Designation,password,username);
        ui->rowContainer->addWidget(row);
        list.push_back(row);
    }

    delete q;
}
