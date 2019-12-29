#include "data/databasecon.h"


databaseCon::databaseCon()
{
    this->constr = XmlManipulation::getData("Database","PATH");
    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName(this->constr);
    if (!Database.open())
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

QSqlQuery* databaseCon::excequte(QString cmdstr)
{
    QSqlQuery* q = new QSqlQuery(Database);
    qDebug() << "databaseCon.cpp (excequte) : exceute : " << Database.databaseName() ;
    if(q->exec(cmdstr))
    {
        qDebug() << "databaseCon.cpp (excequte) : exceute : " << cmdstr ;
        if(q->size() > 0)
        {
            return q;
        }
        return nullptr;
    }
    qDebug() << "databaseCon.cpp (excequte) : not exceute : " << cmdstr ;
    qDebug() << "databaseCon.cpp (excequte) :" << q->lastError().databaseText();
    return nullptr;
}
