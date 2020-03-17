#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>

class GlobalData
{
public:
    GlobalData();
    QString getTagName(int tagname);
    QString getattribute(int tagname);
    enum data{QtyTable,Discount,Tax,customerNameMblNo};


private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
