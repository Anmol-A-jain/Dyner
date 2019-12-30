#include "globaldata.h"

GlobalData::GlobalData()
{
    this->tagname.insert(data::QtyTable,"QtyTable");
    this->attribute.insert(data::QtyTable,"no");

    this->tagname.insert(data::Discount,"Discount");
    this->attribute.insert(data::Discount,"value");

}

QString GlobalData::getTagName(int tagname)
{
    return this->tagname[tagname];
}

QString GlobalData::getattribute(int tagname)
{
    return this->attribute[tagname];
}