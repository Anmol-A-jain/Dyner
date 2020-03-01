#include "server/dynerserver.h"
#include "server/mytcpsocket.h"
#include <QtNetwork>

DynerServer::DynerServer(QObject *parent)
    :QTcpServer(parent)
{

}

void DynerServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << "DynerServer (incomingConnection) : " << socketDescriptor << " Connecting...";

    MyTcpSocket *thread = new MyTcpSocket(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void DynerServer::startServer()
{
    clientlist = new QVector<MyTcpSocket*>;

    quint16 port(1812);

    const QHostAddress &localhost = QHostAddress::LocalHost;
    QStringList ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            ipaddress << address.toString();
        }
    }

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "DynerServer (startServer) : " << "Could not start server";
    }
    else
    {
        qDebug() << "DynerServer (startServer) : " << "Listening to port " << port << "...";
        qDebug() << "DynerServer (startServer) : " << "ip address " << ipaddress << "...";
    }
}


