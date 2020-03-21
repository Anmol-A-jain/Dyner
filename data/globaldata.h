#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

struct ItemData
{
    QString id;
    double qty;
};

struct CartData
{
    int tblNO;
    QVector<ItemData*> item;
};

struct WaiterName
{
    QString name;
    qintptr ID;
};

class GlobalData
{
public:
    GlobalData();
    QString getTagName(int tagname);
    QString getattribute(int tagname);
    enum data{QtyTable,Discount,Tax,customerNameMblNo};

    static void setShadow(QWidget* widget, QColor color = QColor(0,0,0),qreal real = 0.0,qreal radius = 5.0);

    static int contain(int tbl);
    static QVector<CartData*> currentOrder;
    static QVector<WaiterName*> waiter;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
