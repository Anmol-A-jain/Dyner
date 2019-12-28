#ifndef DYNERSERVER_H
#define DYNERSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QVector>
#include "server/mytcpsocket.h"

class DynerServer : public QTcpServer
{
    Q_OBJECT
private:
    QVector<MyTcpSocket*>* clientlist;

public:
    void startServer();
    void sendMessageToClients(QString message);
    DynerServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // DYNERSERVER_H