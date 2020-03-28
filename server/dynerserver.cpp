#include "server/dynerserver.h"
#include "server/mytcpsocket.h"
#include "dyner.h"
#include <QtNetwork>

QVector<MyTcpSocket*>* DynerServer::clientlist = new QVector<MyTcpSocket*>;

DynerServer::DynerServer(QObject *parent)
    :QTcpServer(parent)
{
    this->myParent = parent;
}

DynerServer::~DynerServer()
{
    delete clientlist;
}

void DynerServer::closeAllConnection()
{
    qDebug() << "DynerServer (closeAllConnection) : size : " << clientlist->size();
    for(int i = 0 ; clientlist->size() > i ; ++i)
    {
        clientlist->at(i)->disconnectSocket();
    }
    static QVector<WaiterName*>* q = &GlobalData::waiter;
    for (int i = 0; i < q->count(); ++i)
    {
        q->remove(i);
    }
}

void DynerServer::sendToKitchren(qint16 orderNo, qint16 tblNo, QString name)
{
    emit sendToKitchenParentThread(orderNo,tblNo,name);
}

void DynerServer::updateStatusOfOrder(QString status, int orderNo)
{
    qDebug() << "DynerServer (updateStatusOfOrder) : status :" << status;
    emit updateStatusInOrderWidget(status,orderNo);
}

void DynerServer::addItemInServerManagement()
{
    static_cast<Dyner*>(myParent)->serverSideAddItem();
}

void DynerServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << "DynerServer (incomingConnection) : " << socketDescriptor << " Connecting...";

    //creating a new thread and passing this class as parameter
    MyTcpSocket *thread = new MyTcpSocket(socketDescriptor,this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(dataForKitchen(qint16,qint16,QString)), this, SLOT(sendToKitchren(qint16,qint16,QString)));
    connect(thread, SIGNAL(addItemInServerManagement()), this, SLOT(addItemInServerManagement()));
    connect(thread, SIGNAL(updateStatusOfOrder(QString,int)), this, SLOT(updateStatusOfOrder(QString,int)));
    connect(this, SIGNAL(deleteOrderFromKitchen(qint16)), thread, SLOT(deleteOrderFromKitchen(qint16)));
    connect(this, SIGNAL(sendToKitchenParentThread(qint16,qint16,QString)), thread, SLOT(sendToKitchenChildThread(qint16,qint16,QString)));

    //thread->start();
    clientlist->push_back(thread);

    for (int i = 0; i < clientlist->count(); ++i)
    {
        int id =clientlist->at(i)->getSocketDescriptor();
        if(id == socketDescriptor)
        {
            if(clientlist->at(i) == nullptr)
            {
                qDebug() << "WaiterInformation (on_btnDisconnect_clicked) : nullptr at " << i;
            }
        }
    }
}

QVector<MyTcpSocket *> *DynerServer::getClientlist()
{
    return clientlist;
}

void DynerServer::deleteOrderSignal(qint16 orderNo)
{
    qDebug() << "DynerServer (deleteOrderSignal) : status :" << orderNo;
    emit deleteOrderFromKitchen(orderNo);
}

void DynerServer::startServer()
{
    //clientlist = new QVector<MyTcpSocket*>;

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


