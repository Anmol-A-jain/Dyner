#include "editcategory.h"
#include "ui_editcategory.h"
#include "data/databasecon.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include "header/menu/adminwidget.h"

EditCategory::EditCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCategory)
{
    ui->setupUi(this);
    this->myParent = parent;

    this->loadData();
}

void EditCategory::loadData()
{
    ui->CategoryList->clear();
    databaseCon d;
    QString cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);

    while(q->next())
    {
        ui->CategoryList->addItem(q->value("category").toString());
    }

    delete q;
}

EditCategory::~EditCategory()
{
    delete ui;
}

void EditCategory::on_add_clicked()
{
    databaseCon d;
    if(!ui->CategoryText->text().isEmpty())
    {
        bool isContains = false;

        for(int i = ui->CategoryList->count(); i >= 0 ; --i )
        {
            if(ui->CategoryList->itemText(i) == ui->CategoryText->text())
            {
                isContains = true;
                QMessageBox::critical(this,"Information","Category already exist");
                return;
            }
        }

        if(!isContains)
        {
            QString cmd = "INSERT INTO tblCategoryList VALUES('"+ui->CategoryText->text()+"') ";
            QSqlQuery* q = d.execute(cmd);
            delete q;
            this->loadData();
            QMessageBox::information(this,"Information","category has been added");
        }
    }
}

void EditCategory::on_CategoryList_currentIndexChanged(const QString &arg1)
{
    ui->CategoryText->setText(arg1);
}

void EditCategory::on_searchBox_textChanged(const QString &arg1)
{
    ui->CategoryList->clear();
    databaseCon d;
    QString cmd ;
    if(!ui->searchBox->text().isEmpty())
    {
       cmd = "SELECT category FROM tblCategoryList WHERE category LIKE '%"+ui->searchBox->text()+"%' ORDER BY category";
    }
    else
    {
        cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    }
    QSqlQuery* q = d.execute(cmd);

    qDebug() << "EditCategory.cpp (on_lineEdit_textChanged) : Changed String :" << arg1;
    while(q->next())
    {
        ui->CategoryList->addItem(q->value("category").toString());
    }

    delete q;
}

void EditCategory::on_remove_clicked()
{
    int reply = QMessageBox::critical(this,"Delete Whole Category","<h3>Do you want to Remove Category</h3>\nall the item user this category will be get deleted",QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No);
    if(QMessageBox::Yes == reply)
    {
        databaseCon d;
        QString cmd = "DELETE FROM tblCategoryList WHERE category = '"+ ui->CategoryList->currentText() +"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;

        cmd = "DELETE FROM tblMenu WHERE category = '"+ui->CategoryList->currentText()+"'  ";
        q = d.execute(cmd);
        delete q;

        static_cast<AdminWidget*>(myParent)->loadData();
        this->loadData();
    }
}

void EditCategory::on_update_clicked()
{
    databaseCon d;
    if(!ui->CategoryText->text().isEmpty())
    {
        QString cmd = "UPDATE tblCategoryList SET category = '"+ui->CategoryText->text() +"' WHERE category = '"+ui->CategoryList->currentText()+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;

        cmd = "UPDATE tblMenu SET category = '"+ui->CategoryText->text() +"' WHERE category = '"+ui->CategoryList->currentText()+"'  ";
        q = d.execute(cmd);
        delete q;

        QMessageBox::information(this,"Information","category has been Updated");
        static_cast<AdminWidget*>(myParent)->loadData();
        this->loadData();
    }
}
