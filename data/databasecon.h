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
    static void initDB();
    QSqlQuery* execute(QString cmdstr);

private:
    QString constr;
    QSqlDatabase database;
    static bool isOpen;
    QSqlQuery* q;
};

#endif // DATABASECON_H
