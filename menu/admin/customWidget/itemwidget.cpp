#include "itemwidget.h"
#include "ui_itemwidget.h"
#include "menu/admin/DialogBox/edititem.h"
#include "data/databasecon.h"
#include "../adminwidget.h"
#include <QMessageBox>
#include "data/globaldata.h"

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    ui->setupUi(this);
    this->myParent = parent;

    // adding unicode icon to delete and edit buttons
    ui->deletebtn->setText(QString("\U0001F5D1"));
    ui->editbtn->setText(QString("\U0001F58A"));
    GlobalData::setShadow(this);

}

<<<<<<< HEAD
void ItemWidget::setData(QString id, QString name, QString category, QString price)
{
=======
void ItemWidget::setData(int sr,QString id, QString name, QString category, QString price)
{
    ui->srno->setNum(sr);
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
    ui->ItemId->setText(id);
    ui->name->setText(name);
    ui->Categoty->setText(category);
    ui->Price->setText(price);
}

ItemWidget::~ItemWidget()
{
    delete ui;
}


void ItemWidget::on_editbtn_clicked()
{
    QString id = ui->ItemId->text() ;
    QString name = ui->name->text() ;
    QString category = ui->Categoty->text() ;
    double price = ui->Price->text().toDouble() ;
    EditItem e(id,name,category,price,myParent);
    e.exec();
}

void ItemWidget::on_deletebtn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Delete", "Do You Want To Delete " + ui->name->text() ,QMessageBox::No|QMessageBox::Yes,QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      databaseCon d;

      QString cmd = "DELETE FROM mstTblMenu WHERE id = '"+ ui->ItemId->text() +"'" ;
      QSqlQuery* q = d.execute(cmd);
      if(q != nullptr)
      {
          delete q;
      }
    }
    static_cast<AdminWidget*>(myParent)->loadData();
}
