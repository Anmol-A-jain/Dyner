#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include "data/globaldata.h"
#include <QWidget>

class MyTcpSocket : public QThread
{
public:
    explicit MyTcpSocket(qintptr sockectdescriptor , QObject *parent = nullptr );
    void run();
    QByteArray setAction(int action,QString msg);
    void disconnectSocket();

    qintptr getSocketDescriptor() const;
    QString getClientName() const;

public slots:
    void myReadyRead();
    void myDisconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QObject* myParent;
    QString clientName;
};

#endif // MYTCPSOCKET_H
