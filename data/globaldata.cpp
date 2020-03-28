#include "globaldata.h"
#include "databasecon.h"
#include <QGraphicsDropShadowEffect>
#include <QTextEdit>
#include <QPrinter>
#include <QPrintDialog>

QVector<WaiterName*> GlobalData::waiter;

GlobalData::GlobalData()
{
    this->tagname.insert(data::QtyTable,"QtyTable");
    this->attribute.insert(data::QtyTable,"no");

    this->tagname.insert(data::Discount,"Discount");
    this->attribute.insert(data::Discount,"value");

    this->tagname.insert(data::Tax,"Tax");
    this->attribute.insert(data::Tax,"value");

    this->tagname.insert(data::customerNameMblNo,"tableNo:");
    this->attribute.insert(data::customerNameMblNo,"MblNo-Name");


}

QString GlobalData::getTagName(int tagname)
{
    return this->tagname[tagname];
}

QString GlobalData::getattribute(int tagname)
{
    return this->attribute[tagname];
}

void GlobalData::printBill(QString name, int billId,QWidget* parent)
{
    databaseCon d;
    QString cmd = "SELECT * FROM tblBill WHERE billId = "+QString::number(billId)+"";
    QSqlQuery* q = d.execute(cmd);

    double netAmount = 0;

    QTextEdit edit;
    QString header = QString("%1\t\tBill No:%2").arg(name,billId);
    edit.append(header);
    edit.append("\n");
    edit.append(QString("Name\t\tQty\tPrice"));
    edit.append("--------------------------------------------------------------------");
    while(q->next())
    {
        QString itemName = q->value("ItemName").toString();
        double qty = q->value("QTY").toDouble();
        double price = q->value("price").toDouble();

        netAmount += (qty*price);

        QString record = QString("%1\t\t%2\t%3\n").arg(itemName,QString::number(qty),QString::number(price));
        edit.append(record);
    }
    edit.append("---------------------------------------------------------------------");

    QString footer = QString("\t\tBill Amount (Rs) : %1").arg(netAmount);
    edit.append(footer);
    edit.append("\tThank you");


    QPrinter print;
    print.setPrinterName("Printing Bill");
    QPrintDialog dialog(&print,parent);

    if(dialog.exec() != QDialog::Rejected)
    {
        edit.print(&print);
    }
}

void GlobalData::setShadow(QWidget *widget,QColor color,qreal real,qreal radius  )
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(real);
    effect->setBlurRadius(radius);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}
