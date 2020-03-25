#include "orderdatawidget.h"
#include "ui_orderdatawidget.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include "nestedCustomWidget/statusorderitem.h"

orderDataWidget::orderDataWidget(int orderNo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderDataWidget)
{
    ui->setupUi(this);
    GlobalData::setShadow(this);
    myParent = parent;
    this->orderNo = orderNo;

    ui->label->setText(ui->label->text().append(QString::number(orderNo)));

    databaseCon d;
    QString cmd = "SELECT a.*,b.itemName FROM oderDataFromWaiter a LEFT JOIN mstTblMenu b ON a.Item_id = b.id WHERE orderID = "+QString::number(orderNo)+"" ;
    QSqlQuery* q = d.execute(cmd);

    enum column{i_id,iqty,itblNumber,istatus,inote,iorderID,iName};

    while (q->next())
    {
        QString id = q->value(i_id).toString();
        QString status = q->value(istatus).toString();
        QString itemName = q->value(iName).toString();
        QString qty = q->value(iqty).toString();

        statusOrderItem* item = new statusOrderItem(id,itemName,status,qty,this);
        ui->orderItemContainer->addWidget(item);
        list.push_back(item);
    }

    delete q;

}

orderDataWidget::~orderDataWidget()
{
    deleteVectorData();
    delete ui;
}

void orderDataWidget::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}
