#include "staff.h"
#include "ui_staff.h"

#include "dialogBox/adddesignation.h"
#include "dialogBox/addstaff.h"
#include "dialogBox/editstaff.h"
#include "reportlogin/loginreport.h"

#include "data/databasecon.h"
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>

#include "data/globaldata.h"

staff::staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::staff)
{
    ui->setupUi(this);
    ui->DesignationList->hide();
    this->loadData();

    this->loadComboBoxData();
}

void staff::loadData()
{
    this->deleteVecterData();
    databaseCon d;
    QString cmd = "select s.*,d.salary from mstTblStaff s LEFT JOIN tblDesignation d ON s.designation = d.designation" ;
    QSqlQuery* q = d.execute(cmd);



    for(int i = 0;q->next();++i)
    {
        QString id = q->value("staff_id").toString();
        QString name = q->value("name").toString();
        QString dob = q->value("DOB").toString();
        QString user = q->value("username").toString();
        QString desig = q->value("designation").toString();
        QString mblno = q->value("mbl_no").toString();
        QString address = q->value("address").toString();
        QString city = q->value("city").toString();
        QString salary = q->value("salary").toString();
        QString doj = q->value("DOJ").toString();


        staffwidget *emp = new staffwidget(this);
        stafflist.push_back(emp);


        emp->setData(i+1,id,name,user,desig,salary,mblno,address,city,dob,doj);
        //,dob,doj
        ui->displayAddMenu->addWidget(emp);

         this->updateTotalsal();
    }

    delete q;
}



void staff::deleteVecterData()
{
    for (int i = 0; i < stafflist.count(); ++i)
    {
        delete stafflist[i];
    }
    stafflist.clear();
    qDebug() << "staff.cpp (deleteVecterData) : vector data has been deleted";
}

void staff::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    ui->DesignationList->setSizePolicy(ui->SearchTextBox->sizePolicy());
}

void staff::loadComboBoxData()
{
    ui->DesignationList->clear();
    ui->DesignationList->addItem("All item");
    databaseCon d;
    QString cmd = "SELECT designation FROM tblDesignation ORDER BY designation" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        qDebug() << "staff.cpp (loadComboBoxData) : combo box :" << q->value("designation").toString();
        ui->DesignationList->addItem(q->value("designation").toString());
    }
    delete q;
}

void staff::btnAddDesignationClicked()
{
    emit on_btnAddDesignation_clicked();
}

staff::~staff()
{
    this->deleteVecterData();
    delete ui;
}

void staff::on_btnAddDesignation_clicked()
{
    addDesignation e(this);
    e.exec();
    this->loadComboBoxData();
}

void staff::on_btnAddEmp_clicked()
{
    addStaff add(this);
    add.exec() ;
    this->loadData();
}

void staff::on_DesignationList_currentIndexChanged(int index)
{
    qDebug() << "staff.cpp (on_DesignationList_currentIndexChanged) : index changed : " <<index;
    if(index != 0)
    {
        emit on_SearchButton_clicked();
    }
    else
    {
        this->loadData();
    }

}

void staff::on_menuColumn_currentIndexChanged(int index)
{
    if(index == 4 )
    {
        ui->DesignationList->show();
        ui->SearchTextBox->hide();
    }
    else
    {
        ui->DesignationList->hide();
        ui->SearchTextBox->show();
    }
}

void staff::on_SearchTextBox_textChanged(const QString &arg1)
{
    qDebug() << "staff.cpp (on_SearchTextBox_textChanged) : text changed : " <<arg1;
    emit on_SearchButton_clicked();
}

void staff::on_SearchTextBox_returnPressed()
{
    emit on_SearchButton_clicked();
}

void staff::on_SearchButton_clicked()
{
    QString columnName;
    QString cmd;
    QString searchText = ui->SearchTextBox->text();
    bool iscity = false,isUsername = false, isName = false, isDesignation = false, isAll = false;

    if(!ui->SearchTextBox->text().isEmpty() || !ui->DesignationList->isHidden() )
    {
        if(ui->menuColumn->currentText() == ui->menuColumn->itemText(0))
        {
            isAll = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(1))
        {
            columnName = "id";
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(2))
        {
            columnName = "username";
            isUsername = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(3))
        {
            columnName = "name";
            isName = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(4))
        {
            columnName = "designation";
            isDesignation = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(5))
        {
            columnName = "city";
            iscity = true;
        }

        if(iscity)
        {
            cmd = "SELECT * FROM mstTblStaff WHERE "+ columnName +" = "+ searchText +" ORDER BY staff_id" ;
        }
        else if(isName)
        {
            cmd = "SELECT * FROM mstTblStaff WHERE "+ columnName +" LIKE '%"+ searchText +"%' ORDER BY name" ;
        }
        else if(isAll)
        {
            cmd = "SELECT * FROM mstTblStaff WHERE staff_id = '"+searchText+"' OR name LIKE '%"+ searchText +"%' OR designation LIKE '%"+ searchText +"%' OR username = '"+ searchText +"' OR city = '"+ searchText +"' ORDER BY staff_id" ;
        }
        else if(isDesignation)
        {
            cmd = "SELECT * FROM mstTblStaff WHERE "+ columnName +" = '"+ ui->DesignationList->currentText() +"' ORDER BY staff_id" ;
        }
        else if(isUsername)
        {
            cmd = "SELECT * FROM mstTblStaff WHERE "+ columnName +" LIKE '%"+ searchText +"%' ORDER BY username" ;
        }
        else
        {
            cmd = "SELECT * FROM mstTblStaff WHERE "+ columnName +" LIKE '%"+ ui->SearchTextBox->text() +"%' ORDER BY staff_id" ;
        }
    }
    else
    {
        cmd = "SELECT * FROM mstTblStaff ORDER BY staff_id";
    }

    this->deleteVecterData();
    databaseCon d;
    QSqlQuery* q = d.execute(cmd);
    for(int i = 0;q->next();++i)
    {
        staffwidget *emp = new staffwidget(this);
        stafflist.push_back(emp);
        emp->setData(i+1,q->value("staff_id").toString(),q->value("name").toString(),q->value("username").toString(),q->value("designation").toString(),
                     q->value("salary").toString(),q->value("mbl_no").toString(),q->value("address").toString(),q->value("city").toString(),q->value("DOB").toString(),q->value("DOJ").toString());
        //,q->value("DOB").toString,q->value("DOJ").toString()
        ui->displayAddMenu->addWidget(emp);
    }
    delete q;
}

void staff::resetTotalsal()
{
    ui->t_sal->clear();
    //ui->t_emp->clear();
}
void staff::updateTotalsal()
{
    double sal = 0;
   //int c_emp=0;
    for (int i = 0; i < stafflist.count(); ++i)
    {
        qDebug() << "orderwidget.cpp (updateTotalAmmount ) :  Updated total amount : " << stafflist[i]->getTotal() ;
        sal += stafflist[i]->getTotal();
      //  c_emp += stafflist[i];
    }

    ui->t_sal->setText(QString::number(sal));
 //   ui->t_emp->setText(QString::number(C_emp));


    qDebug() << "staff.cpp (updateTotalAmmount ) :  Updated total amount : " << sal ;//c_emp
}
