#include "databasecon.h"
#include <QtDebug>

databaseCon::databaseCon(QString constr)
{
    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName(constr);
    if (!Database.open())
    {
        qDebug() << "not connected";
    }
    else
    {
        this->constr =constr;
        qDebug() << "connected";
    }

}

QSqlQuery* databaseCon::excequte(QString cmdstr)
{
    QSqlQuery* q = new QSqlQuery(Database);
    if(q->exec(cmdstr))
    {
        return q;
    }
    return nullptr;
}
