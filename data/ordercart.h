#ifndef ORDERCART_H
#define ORDERCART_H

#include <QString>
#include <QMap>

class OrderCart
{
public:
    OrderCart(QString id,QString name,QString ctegry,QString qty,QString rate);
    QMap<int,QString> getdate();
    enum column{Id,Name,Ctegry,Qty,Rate};

private:
    QString id,name,ctegry,qty,rate;

};

#endif // ORDERCART_H
