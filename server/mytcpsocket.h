#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include "data/globaldata.h"
#include <QWidget>

class MyTcpSocket : public QThread
{
    Q_OBJECT
public:
    explicit MyTcpSocket(qintptr sockectdescriptor , QObject *parent = nullptr );
    void run();

    void disconnectSocket();

    qintptr getSocketDescriptor() const;
    QString getClientName() const;
    void sendToKitchen(int orderNo,int tblNo);
    bool isKitchenSocket();



public slots:
    void myReadyRead();
    void myDisconnected();

signals:
    void dataForKitchen(int orderNo,int tblNo);
    void addItemInServerManagement();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QObject* myParent;
    QString clientName;
    bool isKitchen;
    static bool isKitchenConnected;
    static int connectedKitchen;
};

#endif // MYTCPSOCKET_H
