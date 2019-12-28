#include "databasecon.h"
#include <QtDebug>
#include <QSqlError>
#include <QtXml>
#include <QDir>
#include <QFile>

databaseCon::databaseCon()
{

    QString xmlFile = QDir::currentPath() + "/init.xml" , constr ;
    QFile myfile(xmlFile);
    QDomDocument document;
    if(myfile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        if(document.setContent(&myfile))
        {
            QDomElement firstNode = document.firstChildElement() ;
            QDomNodeList itemlist = firstNode.elementsByTagName("Database");

            for (int i = 0; i < itemlist.count() ; ++i)
            {
                QDomNode itemNode = itemlist.at(i);
                if(itemNode.isElement())
                {
                    qDebug() << itemNode.toElement().attribute("PATH");
                    constr = itemNode.toElement().attribute("PATH");
                }
            }
        }
    }


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
        qDebug() << "exceute : " << cmdstr ;
        if(q->size() > 0)
        {
            return q;
        }
        return nullptr;
    }
    qDebug() << "not exceute : " << cmdstr ;
    qDebug() <<  q->lastError().databaseText();
    return nullptr;
}
