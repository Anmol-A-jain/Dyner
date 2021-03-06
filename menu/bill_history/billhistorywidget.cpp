#include "billhistorywidget.h"
#include "ui_billhistorywidget.h"
#include <QDate>
#include <QDebug>
#include "data/databasecon.h"

BillHistoryWidget::BillHistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillHistoryWidget)
{
    ui->setupUi(this);

    ui->rdbToday->click();

    ui->deToDate->setDate(QDate::currentDate());
    ui->deFromDate->setDate(QDate::currentDate());

}

BillHistoryWidget::~BillHistoryWidget()
{
    this->deleteVectorData();
    delete ui;
}

void BillHistoryWidget::SelectionChange()
{
    this->deleteVectorData();
    ui->deFromDate->hide();
    ui->deToDate->hide();
    ui->lblTo->hide();
    ui->lblFrom->hide();

    databaseCon d;

    QString cmd;

    if(ui->rdbToday->isChecked())
    {
        QString date = QDate::currentDate().toString("yyyy-MM-dd");

        cmd = "SELECT a.*,b.Name FROM mstTblBill a LEFT JOIN mstTblcust b ON a.custMblNo = b.custMblNo WHERE a.Date = '"+date+"' ORDER BY a.Date ;" ;
        qDebug() << "billhistorywidget.cpp (SelectionChange) : Today Date : " << date ;
    }
    else if(ui->rdbWeekly->isChecked())
    {
        QDate mDate = QDate::currentDate();
        QDate nDate = mDate.addDays(-7);
        qDebug() << "billhistorywidget.cpp (SelectionChange) : Start Date : " << nDate.toString("yyyy-MM-dd") ;

        QString startDate = nDate.toString("yyyy-MM-dd");
        QString todayDate = mDate.toString("yyyy-MM-dd");

        cmd = "SELECT a.*,b.Name FROM mstTblBill a LEFT JOIN mstTblcust b ON a.custMblNo = b.custMblNo WHERE a.Date BETWEEN '"+startDate+"' AND '"+todayDate+"' ORDER BY a.Date ;" ;
        qDebug() << "billhistorywidget.cpp (SelectionChange) : Start Date : " << startDate ;
        qDebug() << "billhistorywidget.cpp (SelectionChange) : Today Date : " << todayDate ;

    }
    else if(ui->rdbFromToDate->isChecked())
    {
        ui->deFromDate->show();
        ui->deToDate->show();
        ui->lblTo->show();
        ui->lblFrom->show();

        QDate toDate = ui->deToDate->date();
        QDate fromDate = ui->deFromDate->date();

        QString startDate = fromDate.toString("yyyy-MM-dd");

        QString todayDate = toDate.toString("yyyy-MM-dd");

        cmd = "SELECT a.*,b.Name FROM mstTblBill a LEFT JOIN mstTblcust b ON a.custMblNo = b.custMblNo WHERE a.Date BETWEEN '"+startDate+"' AND '"+todayDate+"' ORDER BY a.Date ;" ;
        qDebug() << "billhistorywidget.cpp (SelectionChange) : Start Date : " << startDate ;
        qDebug() << "billhistorywidget.cpp (SelectionChange) : Today Date : " << todayDate ;
    }

    QSqlQuery* q = d.execute(cmd);

    for(int i = 0;q->next();++i)
    {
        QString billId = q->value("billId").toString();
        QString custName = q->value("Name").toString();
        QString date = q->value("Date").toString();
        QString tblNo = q->value("tableNo").toString();
        QString orderType = q->value("orderType").toString();
        QString paymentMode = q->value("paymentMode").toString();
        QString Discount = q->value("Discount").toString();
        QString tax = q->value("tax").toString();
        QString netAmount = q->value("netAmount").toString();

        History* item = new History(i+1,billId,custName,date,tblNo,orderType,paymentMode,Discount,tax,netAmount,this);
        ui->displayOrderRow->addWidget(item);

        list.push_back(item);
    }
}

void BillHistoryWidget::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

void BillHistoryWidget::on_rdbToday_clicked()
{
    this->SelectionChange();
}

void BillHistoryWidget::on_rdbYesterday_clicked()
{
    this->SelectionChange();
}

void BillHistoryWidget::on_rdbWeekly_clicked()
{
    this->SelectionChange();
}

void BillHistoryWidget::on_rdb15Day_clicked()
{
    this->SelectionChange();
}

void BillHistoryWidget::on_rdbMonthly_clicked()
{
    this->SelectionChange();
}

void BillHistoryWidget::on_rdbFromToDate_clicked()
{
    this->SelectionChange();
}

void BillHistoryWidget::on_btnSearch_clicked()
{
    this->SelectionChange();
}
