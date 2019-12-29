#ifndef DATABASECON_H
#define DATABASECON_H


#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QtDebug>
#include <QSqlError>
#include <QtXml>
#include <QDir>
#include <QFile>
#include "data/xmlmanipulation.h"

class databaseCon
{
public:
    databaseCon();
    static void initDB();
    QSqlQuery* excequte(QString cmdstr);

private:
    QString constr;
    QSqlDatabase Database;
};

#endif // DATABASECON_H
