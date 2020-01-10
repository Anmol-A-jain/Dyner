#include "ordercart.h"


OrderCart::OrderCart(QString id,QString name,QString ctegry,QString qty,QString rate)
{
   this->id = id;
   this->name = name;
   this->ctegry = ctegry;
   this->qty = qty;
   this->rate = rate;
}

QMap<int,QString> OrderCart::getdate()
{
    QMap<int,QString> map;
    map.insert(column::Id,this->id);
    map.insert(column::Name,this->name);
    map.insert(column::Ctegry,this->ctegry);
    map.insert(column::Qty,this->qty);
    map.insert(column::Rate,this->rate);

    return map;
}
