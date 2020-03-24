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
    static QVector<MyTcpSocket *>* getClientlist();

public slots:
    void sendToKitchren(qint16 orderNo,qint16 tblNo);

    void addItemInServerManagement();

signals:
    void sendToKitchenParentThread(qint16 orderNo,qint16 tblNo);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // DYNERSERVER_H
