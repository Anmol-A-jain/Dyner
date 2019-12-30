#include "editcategory.h"
#include "ui_editcategory.h"
#include "data/databasecon.h"
#include <QPushButton>
#include <QDebug>

EditCategory::EditCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCategory)
{
    ui->setupUi(this);

    this->loadData();
}

void EditCategory::loadData()
{
    ui->CategoryList->clear();
    databaseCon d;
    QString cmd = "SELECT category FROM categoryList ORDER BY category" ;
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
        QString cmd = "INSERT INTO categoryList VALUES('"+ui->CategoryText->text()+"') ";
        QSqlQuery* q = d.execute(cmd);
        delete q;
        this->loadData();
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
       cmd = "SELECT category FROM categoryList WHERE category LIKE '%"+ui->searchBox->text()+"%' ORDER BY category";
    }
    else
    {
        cmd = "SELECT category FROM categoryList ORDER BY category" ;
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
    databaseCon d;
    QString cmd = "DELETE FROM categoryList WHERE category = '"+ ui->CategoryList->currentText() +"' " ;
    QSqlQuery* q = d.execute(cmd);
    delete q;
    this->loadData();
}

void EditCategory::on_update_clicked()
{
    databaseCon d;
    if(!ui->CategoryText->text().isEmpty())
    {
        QString cmd = "UPDATE categoryList SET category = '"+ui->CategoryText->text() +"' WHERE category = '"+ui->CategoryList->currentText()+"' " ;
        QSqlQuery* q = d.execute(cmd);
        delete q;
        this->loadData();
    }
}
