#include "globaldata.h"
#include <QGraphicsDropShadowEffect>

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

void GlobalData::setShadow(QWidget *widget)
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(0.5);
    effect->setBlurRadius(5.0);
    effect->setColor(QColor(0,0,0));
    widget->setGraphicsEffect(effect);
}
