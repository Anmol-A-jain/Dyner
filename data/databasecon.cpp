#include "data/databasecon.h"
#include <QtDebug>
#include <QSqlError>
#include <QtXml>
#include <QDir>
#include <QFile>
#include "data/xmlmanipulation.h"

databaseCon::databaseCon()
{
    this->constr = XmlManipulation::getData("Database","PATH");
    if(!QSqlDatabase::contains())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }
    else
    {
        database = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    database.setDatabaseName(this->constr);
    if (!database.open())
    {
        qDebug() << "databaseCon.cpp (databaseCon) : not connected";
    }
    else
    {
        qDebug() << "databaseCon.cpp (databaseCon) : connected";
    }
}

void databaseCon::initDB()
{
    // writing database path to XML by colling UDF setXml()
    QString DBFile = QDir::currentPath() + "/DynerDB.db" ;
    XmlManipulation::setData("Database","PATH",DBFile);

    qDebug() << "databaseCon.cpp (initDB) : Is file exist :" << QFile::exists(DBFile);

    // copy DB file to hard disk from resource file
    if(!QFile::exists(DBFile))
    {
        QFile::copy(":/DB/database/DynerDB.db",DBFile);
        QFile::setPermissions(DBFile, QFileDevice::ReadOwner|QFileDevice::WriteOwner);
    }
    qDebug() << "databaseCon.cpp (initDB) : DB file location :" << DBFile ;
}

QSqlQuery* databaseCon::execute(QString cmdstr)
{
    QSqlQuery* q = new QSqlQuery(database);
    qDebug() << "databaseCon.cpp (execute) : DatabaseName : " << database.databaseName() ;
    if(q->exec(cmdstr))
    {
        qDebug() << "databaseCon.cpp (execute) : execute : " << cmdstr ;
        return q;
    }
    qDebug() << "databaseCon.cpp (execute) : not execute : " << cmdstr ;
    qDebug() << "databaseCon.cpp (execute) :" << q->lastError().databaseText();
    return q;
}
