#ifndef DATABASECON_H
#define DATABASECON_H


#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>

class databaseCon
{
public:
    databaseCon();
    QSqlQuery* excequte(QString cmdstr);

private:
    QString constr;
    QSqlDatabase Database;
};

#endif // DATABASECON_H
