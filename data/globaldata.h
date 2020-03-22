#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

// storing waiter data came from android
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


    // storing waiter data came from android
    static QVector<WaiterName*> waiter;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
