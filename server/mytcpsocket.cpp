#include "mytcpsocket.h"
#include "data/allaction.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"

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


    // will write on server side window
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
