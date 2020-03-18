#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

class GlobalData
{
public:
    GlobalData();
    QString getTagName(int tagname);
    QString getattribute(int tagname);
    enum data{QtyTable,Discount,Tax,customerNameMblNo};

    static void setShadow(QWidget* widget);


private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
