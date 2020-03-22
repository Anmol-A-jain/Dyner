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
    void sendToKitchen(QByteArray &data);
    bool isKitchenSocket();



public slots:
    void myReadyRead();
    void myDisconnected();

signals:
    void dataForKitchen(QByteArray &data);


private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QObject* myParent;
    QString clientName;
    bool isKitchen;
};

#endif // MYTCPSOCKET_H
