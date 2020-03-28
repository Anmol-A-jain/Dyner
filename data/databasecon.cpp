#include "data/databasecon.h"
#include <QtDebug>
#include <QSqlError>
#include <QtXml>
#include <QDir>
#include <QFile>
#include "data/xmlmanipulation.h"

QSqlDatabase databaseCon::database;// = QSqlDatabase::addDatabase("QSQLITE");// (!QSqlDatabase::contains()) ? QSqlDatabase::addDatabase("QSQLITE") : QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false) ;

databaseCon::databaseCon()
{
    this->constr = XmlManipulation::getData("Database","PATH");

    database = (!QSqlDatabase::contains()) ? QSqlDatabase::addDatabase("QSQLITE") : QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false) ;

    if(!database.isOpen())
    {
        database.setDatabaseName(this->constr);
        if (!database.open())
        {
            qDebug() << "databaseCon.cpp (databaseCon) : not connected";
        }
        else
        {
            qDebug() << "databaseCon.cpp (databaseCon) : connected";
            delete this->execute("PRAGMA foreign_keys = ON;");
        }
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
    else
    {
        qDebug() << "databaseCon.cpp (initDB) : DB file Exist :" << DBFile ;
    }
    qDebug() << "databaseCon.cpp (initDB) : DB file location :" << DBFile ;
}

QSqlQuery* databaseCon::execute(QString cmd)
{
    QSqlQuery* q = new QSqlQuery(database);
    qDebug() << "databaseCon.cpp (execute) : DatabaseName : " << database.databaseName() ;
    if(q->exec(cmd))
    {
        qDebug() << "databaseCon.cpp (execute) : execute : " << cmd ;
        return q;
    }
    qDebug() << "databaseCon.cpp (execute) : not execute : " << cmd ;
    qDebug() << "databaseCon.cpp (execute) :" << q->lastError().databaseText();
    return q;

//    database = QSqlDatabase::addDatabase("QSQLITE");
//    QString constr = XmlManipulation::getData("Database","PATH");

//    database.setDatabaseName(constr);

//    QSqlQuery* q = new QSqlQuery(database);

//    if(!database.isOpen())
//    {
//        if (!database.open())
//        {
//            qDebug() << "databaseCon.cpp (execute) : not connected";
//        }
//        else
//        {
//            qDebug() << "databaseCon.cpp (execute) : connected";


//            qDebug() << "databaseCon.cpp (execute) : DatabaseName : " << database.databaseName() ;

//            QString PROGMA = "PRAGMA foreign_keys = ON;";

//            if(q->exec(PROGMA))
//            {
//                qDebug() << "databaseCon.cpp (execute) : execute : " << PROGMA ;
//            }
//            else
//            {
//                qDebug() << "MyTcpSocket.cpp (execute) : not execute : " << PROGMA ;
//            }
//            if(q->exec(cmd))
//            {
//                qDebug() << "MyTcpSocket.cpp (execute) : execute : " << cmd ;
//                return q;
//            }
//            qDebug() << "MyTcpSocket.cpp (execute) : not execute : " << cmd ;
//            qDebug() << "MyTcpSocket.cpp (execute) :" << q->lastError().databaseText();
//            return q;

//            //delete this->execute("PRAGMA foreign_keys = ON;");
//        }
//    }
//    return q;
}

QSqlDatabase &databaseCon::getDatabase()
{
    return database;
}
