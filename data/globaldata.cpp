#include "globaldata.h"
#include <QGraphicsDropShadowEffect>

QVector<CartData*> GlobalData::currentOrder;
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

void GlobalData::setShadow(QWidget *widget,QColor color,qreal real,qreal radius  )
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(real);
    effect->setBlurRadius(radius);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}

int GlobalData::contain(int tbl)
{
    QVector<CartData*>* q = &currentOrder;

    for (int i = 0; i < q->count(); ++i)
    {
        if(q->at(i)->tblNO == tbl) return i;
    }
    return 0;
}
