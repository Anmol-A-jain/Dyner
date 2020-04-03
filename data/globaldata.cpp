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

void GlobalData::printBill(QString name, int billId, QString netAmount, QString tax,QString discount,QString finalAmount, QWidget* parent)
{
    databaseCon d;
    QString cmd = "SELECT * FROM tblBill WHERE billId = "+QString::number(billId)+"";
    QSqlQuery* q = d.execute(cmd);

    //double netAmount = 0;

    QTextEdit edit;
    QString header = QString("Name: %1\nBill No:%2").arg(name,QString::number(billId));
    edit.append(header);
    edit.append("\n");
    edit.append(QString("Name\t\tQty\tPrice"));
    edit.append("--------------------------------------------------------------------");
    while(q->next())
    {
        QString itemName = q->value("ItemName").toString();
        double qty = q->value("QTY").toDouble();
        double price = q->value("price").toDouble();

        int charLimit = 15;

        if(itemName.length() < charLimit ) {itemName.append("\t");}
        else
        {
            int loopCount = (itemName.length()/charLimit);

            for (int i = 1; i <= loopCount; ++i)
            {
                itemName.insert((i*charLimit),'\n');
            }
            itemName.append("\t");
        }
        QString record = QString("%1\t%2\t%3\n").arg(itemName,QString::number(qty),QString::number(price));
        edit.append(record);
    }
    edit.append("---------------------------------------------------------------------");

    QString footer = QString("\tNet Amount (Rs) :\t %1").arg(netAmount);
    edit.append(footer);

    QString dicountRow = QString("\tDiscount (in %) :\t %1").arg(discount);
    edit.append(dicountRow);

    QString taxRow = QString("\tTax (Rs) :\t\t %1").arg(tax);
    edit.append(taxRow);

    QString finalAmountRow = QString("\tTotal Amount (Rs) :\t %1").arg(finalAmount);
    edit.append(finalAmountRow);

    edit.append("\n\n\tThank you");

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
