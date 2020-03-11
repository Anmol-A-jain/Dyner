#include "mytcpsocket.h"
#include "data/allaction.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"
#include "data/databasecon.h"

MyTcpSocket::MyTcpSocket(qintptr ID , QObject *parent )
    :QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyTcpSocket::run()
{
        // thread starts here
        qDebug() << " Thread started";

        socket = new QTcpSocket();

        // set the ID
        if(!socket->setSocketDescriptor(this->socketDescriptor))
        {
            // something's wrong, we just emit a signal
            qDebug() << "error!!" ;
            return;
        }

        // connect socket and signal
        // note - Qt::DirectConnection is used because it's multithreaded
        // This makes the slot to be invoked immediately, when the signal is emitted.

        connect(socket, &QTcpSocket::readyRead, this, &MyTcpSocket::myReadyRead, Qt::DirectConnection);
        connect(socket, &QTcpSocket::disconnected , this, &MyTcpSocket::myDisconnected  );

        // We'll have multiple clients, we want to know which is which
        qDebug() << socketDescriptor << " Client connected";

        // make this thread a loop,
        // thread will stay alive so that signal/slot to function properly
        // not dropped out in the middle when thread dies

        exec();
}

void MyTcpSocket::myReadyRead()
{
    // get the information
    QByteArray dataIn = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << dataIn;

    QDataStream in(&dataIn,QIODevice::ReadWrite);


    qint16 action;
    in >> action;

    qDebug() << socketDescriptor << " Data in: " << dataIn << ":" << action;

    qDebug() << "serverConnection (myReadReady) : action : " << action;

    switch (action)
    {
        case ALLAction::error :
        {
            qDebug() << "serverConnection (myReadReady) : list : " << dataIn;
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            //sending total table Quantity..

            QByteArray dataOut ;

            QDataStream out(&dataOut,QIODevice::ReadWrite);

            GlobalData g;
            qint16 tblNo =  XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) ).toInt();
            qint16 i = ALLAction::getTotaltableNo;

            //sending action and total table no
            out << i;
            out << tblNo;

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            int size = socket->write(dataOut);
            socket->flush();

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg size : " << size ;

            break;

        }
        case ALLAction::menuData :
        {
            //sending total table Quantity..
            QByteArray dataOut ;
            QDataStream out(&dataOut,QIODevice::ReadWrite);

            qint16 i = ALLAction::menuData;
            out << i;

            databaseCon d;
            QString cmd = "select * from mstTblMenu order by id" ;
            QSqlQuery* q = d.execute(cmd);

            qint16 count = 0 ;
            for( ; q->next() ; ++count);
            out << count;

            q->seek(-1);

            while( q->next())
            {
                out << q->value("id").toString() << q->value("itemName").toString() << q->value("category").toString() << q->value("Price").toDouble();
            }

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            socket->write(dataOut);
            socket->flush();

            delete q;
            break;
        }
        default:
        {
            qDebug() << "serverConnection (myReadReady) : default case called : " << dataIn;
        }
    }

    /*// get the information
    QString data = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << data;

    QStringList list = data.split('~');

    bool isFirst = true;
    QStringList dataList ;
    int action;

    for(int i = 0 ;i < list.length() ; ++i)
    {
        if(isFirst)
        {
            action = list.at(i).toInt() ;
            isFirst = false;
        }
        else
        {
            dataList.push_back(list.at(i));
        }
    }

    qDebug() << "serverConnection (myReadReady) : action : " << action;
    qDebug() << "serverConnection (myReadReady) : value : " << dataList;

    switch (action)
    {
        case ALLAction::error :
        {
            qDebug() << "serverConnection (myReadReady) : list : " << list;
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            //sending total table Quantity..
            GlobalData g;
            QString tblNo =  XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) );

            QByteArray msg = setAction(ALLAction::getTotaltableNo,tblNo);

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << msg ;
            socket->write(msg);

            break;
        }
        default:
        {
            qDebug() << "serverConnection (myReadReady) : default case called : " << data;
        }
    }

    // will write on server side window*/
}

void MyTcpSocket::myDisconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

QByteArray MyTcpSocket::setAction(int action, QString msg)
{
    QByteArray data = QByteArray::number(action) + "~" ;
    data.append(msg);
    return data;
}

void MyTcpSocket::disconnectSocket()
{
    socket->disconnectFromHost();
}
