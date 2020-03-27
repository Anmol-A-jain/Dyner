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
    QSqlQuery* execute(QString cmd);

    static QSqlDatabase &getDatabase();

private:
    QString constr;
    static QSqlDatabase database;
    QSqlQuery* q;
};

#endif // DATABASECON_H
