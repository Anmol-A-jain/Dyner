#include "orderwidget.h"
#include "ui_orderwidget.h"
#include <QDebug>
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include "DialogBox/addorderitem.h"
#include "data/databasecon.h"

OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
    ui-> lblTblNo->hide();
    ui->cmbTblNo->hide();
    ui->lblAddres->hide();
    ui->cmbAdderess->hide();

    GlobalData g;
    int totalTable = XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable)).toInt();

    for (int i = 1 ; i <= totalTable ; ++i )
    {
        ui->cmbTblNo->addItem(QString::number(i));
    }
    this->loadData();
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

int OrderWidget::getTblNo()
{
    qDebug() << "orderwidget.cpp (getTblNo ) : index : " << ui->cmbTblNo->currentText().toInt();
    return ui->cmbTblNo->currentText().toInt();
}

void OrderWidget::loadData()
{
    this->deleterVecterData();
    databaseCon d;
    QString cmd = "SELECT a.*, b.itemName , b.Price , b.category  FROM tblTempOrder a LEFT JOIN mstTblMenu b ON a.item_id = b.id;" ;
    QSqlQuery* q = d.execute(cmd);

    while (q->next())
    {

        if(q->value(0).toInt() == this->getTblNo() && ui->cmbOrrderType->currentText() == "Table No" )
        {
            QString id = q->value(1).toString();
            double qty = q->value(2).toDouble();
            QString name = q->value(3).toString();
            double price = q->value(4).toDouble();
            QString category = q->value(5).toString();

            displayWidget* itemData = new displayWidget(id,name,category,qty,price,this->getTblNo(),this);
            ui->displayOrderRow->addWidget(itemData);
            list.push_back(itemData);
        }

    }
}

void OrderWidget::deleterVecterData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

void OrderWidget::on_cmbOrrderType_currentIndexChanged(int index)
{
    qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : index : " << index;
    switch (index)
    {
        case 0:
        {
            // self pick up
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->hide();
            ui->cmbTblNo->hide();
            ui->lblAddres->hide();
            ui->cmbAdderess->hide();
            break;
        }
        case 1:
        {
            // Delivery
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->hide();
            ui->cmbTblNo->hide();
            ui->lblAddres->show();
            ui->cmbAdderess->show();
            break;
        }
        case 2:
        {
            // Table no
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->show();
            ui->cmbTblNo->show();
            ui->lblAddres->hide();
            ui->cmbAdderess->hide();
            break;
        }
    }
}

void OrderWidget::on_pushButton_clicked()
{
   AddOrderItem aoi(this);
   aoi.exec();

}

void OrderWidget::on_cmbTblNo_currentTextChanged(const QString &arg1)
{
    qDebug() << "orderwidget.cpp (on_cmbTblNo_currentTextChanged) : cmbTblNo changed : " << arg1 ;
    this->deleterVecterData();
    this->loadData();
}

void OrderWidget::on_cmbOrrderType_currentTextChanged(const QString &arg1)
{
    qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentTextChanged) : cmbTblNo changed : " << arg1 ;
    this->deleterVecterData();
    this->loadData();
}
