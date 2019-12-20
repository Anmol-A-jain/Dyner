#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QThread>
#include <QDebug>
#include <QTcpSocket>

class MyTcpSocket : public QThread
{
public:
    explicit MyTcpSocket(qintptr sockectdescriptor , QObject *parent = nullptr );
    void run();

public slots:
    void myReadyRead();
    void myDisconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

};

#endif // MYTCPSOCKET_H
