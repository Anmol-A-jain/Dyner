#ifndef DYNERSERVER_H
#define DYNERSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QVector>
#include "server/mytcpsocket.h"
#include <QWidget>

class DynerServer : public QTcpServer
{
    Q_OBJECT
private:
    static QVector<MyTcpSocket*>* clientlist;
    QObject* myParent;

public:
    void startServer();
    void sendMessageToClients(QString message);
    DynerServer(QObject *parent = nullptr);
    ~DynerServer();
    static void closeAllConnection();

public slots:
    void sendToKitchren(QByteArray data);

    static QVector<MyTcpSocket *>* getClientlist();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // DYNERSERVER_H
