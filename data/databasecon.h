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

    static QSqlDatabase &getDatabase();

private:
    QString constr;
    static QSqlDatabase database;
    static bool isOpen;
    QSqlQuery* q;
};

#endif // DATABASECON_H
