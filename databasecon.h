#ifndef DATABASECON_H
#define DATABASECON_H


#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class databaseCon
{
public:
    databaseCon(QString consr);
    QSqlQuery* excequte(QString cmdstr);

private:
    QString constr;
    QSqlDatabase Database;
};

#endif // DATABASECON_H
