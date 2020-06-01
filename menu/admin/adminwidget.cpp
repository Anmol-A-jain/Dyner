#include "adminwidget.h"
#include "ui_adminwidget.h"
#include "data/databasecon.h"
#include "DialogBox/additem.h"
#include "DialogBox/edittablenoanddiscount.h"
#include "DialogBox/editcategory.h"
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"
#include "menu/login/DialogBox/changepassword.h"


AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);

    ui->categoryList->hide();
    this->loadData();
    this->loadInfo();
    this->loadComboBoxData();
}

void AdminWidget::loadData()
{
    this->deleteVecterData();
    databaseCon d;
    QString cmd = "select * from mstTblMenu order by id" ;
    QSqlQuery* q = d.execute(cmd);
    while( q->next())
    {
        ItemWidget *item = new ItemWidget(this);
        itemlist.push_back(item);
        item->setData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString());
        ui->displayAddMenu->addWidget(item);
    }

    delete q;
}

void AdminWidget::loadInfo()
{
    GlobalData g;
    ui->noOfTable->setText(XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) ) );
    ui->discount->setText(XmlManipulation::getData(g.getTagName(g.Discount),g.getattribute(g.Discount)));
    ui->txtTax->setText(XmlManipulation::getData( g.getTagName(g.Tax),g.getattribute(g.Tax) ) );
}

void AdminWidget::deleteVecterData()
{
    for (int i = 0; i < itemlist.count(); ++i)
    {
        delete itemlist[i];
    }
    itemlist.clear();
    qDebug() << "AdminWidget.cpp (deleteVecterData) : vector data has been deleted";
}

void AdminWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    ui->categoryList->setSizePolicy(ui->SearchTextBox->sizePolicy());
}

void AdminWidget::loadComboBoxData()
{
    ui->categoryList->clear();
    ui->categoryList->addItem("All item");
    databaseCon d;
    QString cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        qDebug() << "AdminWidget.cpp (loadComboBoxData) : combo box :" << q->value("category").toString();
        ui->categoryList->addItem(q->value("category").toString());
    }
    delete q;
}

void AdminWidget::btnEditCategoryClicked()
{
    emit on_btnEditCategory_clicked();
}

AdminWidget::~AdminWidget()
{
    this->deleteVecterData();
    delete ui;
}

void AdminWidget::on_AddItem_clicked()
{
    addItem add(this);
    add.exec() ;
    this->loadData();
}

void AdminWidget::on_editButton_clicked()
{
    EditTableNoAndDiscount e;
    e.exec();
    this->loadInfo();
}

void AdminWidget::on_SearchButton_clicked()
{
    QString columnName;
    QString cmd;
    QString searchText = ui->SearchTextBox->text();
    bool isPrice = false, isName = false, isCategory = false, isAll = false;

    if(!ui->SearchTextBox->text().isEmpty() || !ui->categoryList->isHidden() )
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
            columnName = "itemName";
            isName = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(3))
        {
            columnName = "category";
            isCategory = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(4))
        {
            columnName = "Price";
            isPrice = true;
        }

        if(isPrice)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" = "+ searchText +" ORDER BY id" ;
        }
        else if(isName)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" LIKE '%"+ searchText +"%' ORDER BY id" ;
        }
        else if(isAll)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE id = '"+searchText+"' OR itemName LIKE '%"+ searchText +"%' OR category LIKE '%"+ searchText +"%' OR Price = '"+ searchText +"' ORDER BY id" ;
        }
        else if(isCategory)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" = '"+ ui->categoryList->currentText() +"' ORDER BY id" ;
        }
        else
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" LIKE '%"+ ui->SearchTextBox->text() +"%' ORDER BY id" ;
        }
    }
    else
    {
        cmd = "SELECT * FROM mstTblMenu ORDER BY id";
    }

    this->deleteVecterData();
    databaseCon d;
    QSqlQuery* q = d.execute(cmd);
    while( q->next() )
    {
        ItemWidget *item = new ItemWidget(this);
        itemlist.push_back(item);
        item->setData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString());
        ui->displayAddMenu->addWidget(item);
    }
    delete q;
}

void AdminWidget::on_SearchTextBox_returnPressed()
{
    emit on_SearchButton_clicked();
}

void AdminWidget::on_SearchTextBox_textChanged(const QString &arg1)
{
    qDebug() << "AdminWidget.cpp (on_SearchTextBox_textChanged) : text changed : " <<arg1;
    emit on_SearchButton_clicked();
}

void AdminWidget::on_btnEditCategory_clicked()
{
    EditCategory e(this);
    e.exec();
    this->loadComboBoxData();
}

void AdminWidget::on_menuColumn_currentIndexChanged(int index)
{
    if(index == 3 )
    {
        ui->categoryList->show();
        ui->SearchTextBox->hide();
    }
    else
    {
        ui->categoryList->hide();
        ui->SearchTextBox->show();
    }
}


void AdminWidget::on_categoryList_currentIndexChanged(int index)
{
    qDebug() << "AdminWidget.cpp (on_categoryList_currentIndexChanged) : index changed : " <<index;
    if(index != 0)
    {
        emit on_SearchButton_clicked();
    }
    else
    {
        this->loadData();
    }
}

void AdminWidget::on_btnPassword_clicked()
{
    ChangePassword c;
    c.exec();
}
