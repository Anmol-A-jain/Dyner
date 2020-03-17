#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QThread>
#include <QDebug>
#include <QTcpSocket>


struct ItemData
{
    QString id;
    double qty;
};

struct CartData
{
    int tblNO;
    ItemData* item;
};

class MyTcpSocket : public QThread
{
public:
    explicit MyTcpSocket(qintptr sockectdescriptor , QObject *parent = nullptr );
    void run();
    QByteArray setAction(int action,QString msg);
    void disconnectSocket();

public slots:
    void myReadyRead();
    void myDisconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QVector<CartData*> currentOrder;
};

#endif // MYTCPSOCKET_H
