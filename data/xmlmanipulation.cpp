#include "xmlmanipulation.h"

XmlManipulation::XmlManipulation()
{

}

QString XmlManipulation::getData(QString tagname, QString attribute)
{
    QString xmlFile = QDir::currentPath() + "/init.xml" ;
    QString value = "" ;
    QFile myfile(xmlFile);
    QDomDocument document;
    if(myfile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        if(document.setContent(&myfile))
        {
            QDomElement firstNode = document.firstChildElement() ;
            QDomNodeList itemlist = firstNode.elementsByTagName(tagname);

            for (int i = 0; i < itemlist.count() ; ++i)
            {
                QDomNode itemNode = itemlist.at(i);
                if(itemNode.isElement())
                {
                    qDebug() << "XmlManipulation.cpp (getData) : " <<itemNode.toElement().attribute(attribute);
                    value = itemNode.toElement().attribute(attribute);
                }
            }
        }
    }
    return value;
}

void XmlManipulation::setData(QString tagname, QString attribute, QString value)
{
    QString xmlFile = QDir::currentPath() + "/init.xml" ;
    QFile myfileRead(xmlFile);

    if(QFile::exists(xmlFile))
    {
        QDomDocument document;
        if(myfileRead.open(QIODevice::ReadWrite | QIODevice::Text) )
        {
            if(document.setContent(&myfileRead))
            {
                //Write xml
                QDomElement root = document.firstChildElement() ;
                document.appendChild(root);
                QDomNodeList itemlist = root.elementsByTagName(tagname);
                if(itemlist.count() == 0 )
                {
                    QDomElement db = document.createElement(tagname);
                    db.setAttribute(attribute,value);
                    root.appendChild(db);
                    myfileRead.close();

                    QFile myfileWrite(xmlFile);
                    if(myfileWrite.open(QIODevice::WriteOnly | QIODevice::Text) )
                    {
                        QTextStream stream(&myfileWrite);
                        stream << document.toString();
                        myfileWrite.close();
                    }
                }
            }
        }
    }
    else
    {
        //Write xml
        QDomDocument document;
        QDomElement root = document.createElement("Dyner");
        document.appendChild(root);
        QDomElement db = document.createElement(tagname);
        db.setAttribute(attribute,value);
        root.appendChild(db);

        QFile myfile(xmlFile);
        if(myfile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream stream(&myfile);
            stream << document.toString();
            myfile.close();
        }

    }
    qDebug() << "XmlManipulation.cpp (setData) : xml file location :" << xmlFile ;
}
