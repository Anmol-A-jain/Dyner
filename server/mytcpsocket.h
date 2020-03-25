#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include "data/globaldata.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

class MyTcpSocket : public QThread
{
    Q_OBJECT
public:
    explicit MyTcpSocket(qintptr sockectdescriptor , QObject *parent = nullptr );
    void run();

    void disconnectSocket();

    qintptr getSocketDescriptor() const;
    QString getClientName() const;
    bool isKitchenSocket();
    //QSqlQuery* execute(QString cmdstr);

    static bool getIsKitchenConnected();

public slots:
    void myReadyRead();
    void myDisconnected();
    void sendToKitchenChildThread(qint16 orderNo, qint16 tblNo, QString name);

signals:
    void dataForKitchen(qint16 orderNo,qint16 tblNo,QString name);
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
