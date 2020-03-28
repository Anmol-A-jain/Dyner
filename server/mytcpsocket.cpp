#include "mytcpsocket.h"
#include "server/dynerserver.h"
#include "dyner.h"
#include "data/allaction.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include <QSqlError>

bool MyTcpSocket::isKitchenConnected = false;
int MyTcpSocket::connectedKitchen = 0;

MyTcpSocket::MyTcpSocket(qintptr ID , QObject *parent )
    :QThread(parent)
{
    this->socketDescriptor = ID;
    this->myParent = parent;
    this->isKitchen = false;

    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        qDebug() << "error!!" ;
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    // This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, &QTcpSocket::readyRead, this, &MyTcpSocket::myReadyRead, Qt::DirectConnection);
    connect(socket, &QTcpSocket::disconnected , this, &MyTcpSocket::myDisconnected );

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

}

void MyTcpSocket::run()
{
        // thread starts here
        qDebug() << " Thread started";

        socket = new QTcpSocket();

        // set the ID
        if(!socket->setSocketDescriptor(this->socketDescriptor))
        {
            // something's wrong, we just emit a signal
            qDebug() << "error!!" ;
            return;
        }

        // connect socket and signal
        // note - Qt::DirectConnection is used because it's multithreaded
        // This makes the slot to be invoked immediately, when the signal is emitted.

        connect(socket, &QTcpSocket::readyRead, this, &MyTcpSocket::myReadyRead, Qt::DirectConnection);
        connect(socket, &QTcpSocket::disconnected , this, &MyTcpSocket::myDisconnected );

        // We'll have multiple clients, we want to know which is which
        qDebug() << socketDescriptor << " Client connected";

        // make this thread a loop,
        // thread will stay alive so that signal/slot to function properly
        // not dropped out in the middle when thread dies

        exec();
}

void MyTcpSocket::myReadyRead()
{

    // get the information
    //serverClient->waitForReadyRead(1000);
    int bytes = socket->bytesAvailable();
    QByteArray dataIn ;//= serverClient->readAll();
    qDebug() << "MyTcpSocket (myReadReady) : Data available count: " << bytes;

    while(bytes != 0)
    {
        if(bytes < 1000 )
        {
            dataIn.append(socket->readAll());
            bytes = 0;
        }
        else
        {
            dataIn.append(socket->read(1000));
            bytes -= 1000;
        }
        qDebug() << "MyTcpSocket (myReadReady) : Data in: " << dataIn;
        qDebug() << "MyTcpSocket (myReadReady) : Data count: " << bytes;
    }

    // get the information
    /*QByteArray dataIn = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << dataIn;*/

    QDataStream in(&dataIn,QIODevice::ReadWrite);


    qint16 action;
    in >> action;

    QString msg;
    qint16 type = 0;

    enum msgType{warning,informative,critical};
    if((!isKitchenConnected && action == ALLAction::cartData) || (!isKitchenConnected && action == ALLAction::getCustInfo) )
    {
        action = ALLAction::showNotification;
        type = critical;
        msg = "kitchen is not connected";
    }

    qDebug() << socketDescriptor << " Data in: " << dataIn << ":" << action;

    qDebug() << "MyTcpSocket (myReadReady) : action : " << action;
    qDebug() << "MyTcpSocket (myReadReady) : action : " << action;

    switch (action)
    {

        // android management
        case ALLAction::error :
        {
            qDebug() << "MyTcpSocket (myReadReady) : list : " << dataIn;
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            //sending total table Quantity..

            QVector<WaiterName*>* q = &GlobalData::waiter;

            QString name;
            in >> name;

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : client name : " << name ;


            WaiterName* waiter = new WaiterName;
            waiter->ID = this->socketDescriptor;
            waiter->name = name;

            q->push_back(waiter);

            emit addItemInServerManagement();

            QByteArray dataOut ;

            QDataStream out(&dataOut,QIODevice::ReadWrite);

            GlobalData g;
            qint16 tblNo =  XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) ).toInt();
            qint16 i = ALLAction::getTotaltableNo;

            //sending action and total table no
            out << i;
            out << tblNo;

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            int size = socket->write(dataOut);
            socket->flush();

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : sending msg size : " << size ;

            break;

        }

        case ALLAction::menuData :
        {
            //sending total table Quantity..
            QByteArray dataOut ;
            QDataStream out(&dataOut,QIODevice::ReadWrite);

            qint16 i = ALLAction::menuData;
            out << i;

            databaseCon d;
            QString cmd = "select * from mstTblMenu order by id" ;
            QSqlQuery* q = d.execute(cmd);

            qint16 count = 0 ;
            for( ; q->next() ; ++count);
            out << count;

            q->seek(-1);

            while( q->next())
            {
                out << q->value("id").toString() << q->value("itemName").toString() << q->value("category").toString() << q->value("Price").toDouble();
            }

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            int bytes = socket->write(dataOut);
            socket->flush();
            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : sending total byets : " << bytes ;

            delete q;
            break;
        }
        case ALLAction::getCustInfo:
        {
            int tblNo ;
            in >> tblNo;

            QByteArray dataOut ;
            QDataStream out(&dataOut,QIODevice::ReadWrite);
            GlobalData g;
            QString attribute = g.getattribute(GlobalData::customerNameMblNo);
            QStringList list = attribute.split("-");

            QString name =  XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(tblNo),list.at(1));
            QString mblNo =  XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(tblNo),list.at(0));
            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : customer data : " << name <<":"<< mblNo ;

            qint16 i = ALLAction::getCustInfo;
            out << i << name << mblNo;

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            socket->write(dataOut);
            socket->flush();
            break;
        }
        case ALLAction::cartData :
        {
            qint16 tblNo = -1,count = 0 ;
            QString mblNo,name;

            in >> tblNo;
            in >> count;

            in >> name;
            in >> mblNo;

            GlobalData g;
            QString attribute = g.getattribute(GlobalData::customerNameMblNo);
            QStringList list = attribute.split("-");

            XmlManipulation::setData(g.getTagName(GlobalData::customerNameMblNo)+QString::number(tblNo),list.at(0),mblNo);
            XmlManipulation::setData(g.getTagName(GlobalData::customerNameMblNo)+QString::number(tblNo),list.at(1),name);

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::cartData : table no : " << tblNo;
            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::cartData : total item : " << count;


            int lastID = 1;

            databaseCon d;
            QString cmd = "SELECT orderID FROM oderDataFromWaiter ORDER BY orderID desc LIMIT 1 " ;
            QSqlQuery* q = d.execute(cmd) ;

            if(q->next())
            {
                lastID = q->value("orderID").toInt() + 1;
            }

            for (int i = 0; i < count; ++i)
            {
                QString id,note;
                double qty;

                in >> id;
                in >> note;
                in >> qty;

                qDebug() << "MyTcpSocket (myReadReady) : ALLAction::cartData : item id : " << id;
                qDebug() << "MyTcpSocket (myReadReady) : ALLAction::cartData : item note : " << note;
                qDebug() << "MyTcpSocket (myReadReady) : ALLAction::cartData : item qty : " << qty;

                double preQty = 0;


                cmd = "INSERT INTO oderDataFromWaiter(Item_id,qty,tblNo,status,note,orderID) VALUES('"+id+"' ,"+QString::number(qty)+","+QString::number(tblNo)+",'sending','"+note+"',"+QString::number(lastID)+" );";
                q = d.execute(cmd) ;

                cmd = "select * from tblTempOrder WHERE table_no =" + QString::number(tblNo) +" AND item_id = '" + id + "'";
                q=  d.execute(cmd);

                int size;
                for (size = 0; size < q->next(); ++size)
                {
                    preQty = q->value("qty").toDouble();
                }

                if(size == 0)
                {
                    cmd = "INSERT INTO tblTempOrder VALUES("+QString::number(tblNo)+",'"+id+"','"+QString::number(qty)+"')" ;
                    q = d.execute(cmd);
                }
                else
                {
                    cmd = "UPDATE tblTempOrder SET qty = '"+QString::number(qty+preQty)+"' WHERE item_id = '"+id+"' ";
                    q = d.execute(cmd);
                }
                delete q;
            }

            emit dataForKitchen(lastID,tblNo,name);

            QByteArray dataOut;

            QDataStream out(&dataOut,QIODevice::ReadWrite);
            type = informative;
            msg = "Order Has been placed \n Order No : " + QString::number(lastID);
            qint16 actionOut = ALLAction::showNotification;
            out << actionOut;

            out << type << msg;

            socket->write(dataOut);

            //static_cast<DynerServer*>(myParent)->sendToKitchren(dataOut);
            break;
        }
        case ALLAction::showNotification:
        {
            QByteArray dataOut;

            QDataStream out(&dataOut,QIODevice::ReadWrite);

            qint16 actionOut = ALLAction::showNotification;

            out << actionOut;

            out << type << msg;

            socket->write(dataOut);

            break;
        }


        // kitchen management
        case ALLAction::kitchenInfo:
        {
            QVector<WaiterName*>* q = &GlobalData::waiter;

            QString name;
            in >> name;

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::kitchenInfo : name  : " << name ;
            WaiterName* waiter = new WaiterName;
            waiter->ID = this->socketDescriptor;
            waiter->name = name;
            q->push_back(waiter);


            QString kitchenName = "kitchen";

            if(name == kitchenName)
            {
                isKitchen = true ;
            }

            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::kitchenInfo : is kichen : " << isKitchen ;


            qDebug() << "MyTcpSocket (myReadReady) : ALLAction::kitchenInfo : name  : " << q->count() ;

            emit addItemInServerManagement();

            isKitchenConnected = true;
            connectedKitchen++;

            break;
        }
        case ALLAction::individual:
        {
            qint16 orderNo;
            QString status ;
            in >> orderNo >> status;
            databaseCon d;
            QString cmd = "UPDATE oderDataFromWaiter SET status = '"+status+"' WHERE orderID = "+QString::number(orderNo)+";";
            delete d.execute(cmd) ;

            emit updateStatusOfOrder(status,orderNo);

            break;
        }
        case ALLAction::deleteOrder:
        {

            break;
        }
        default:
        {
            qDebug() << "MyTcpSocket (myReadReady) : default case called : " << dataIn;
        }
    }

    // will write on server side window*/
}

void MyTcpSocket::myDisconnected()
{
    qDebug() << "MyTcpSocket (myDisconnected) : id :" << socketDescriptor << " Disconnected";

    QVector<MyTcpSocket*>* list =DynerServer::getClientlist();

    for (int i = 0; i < list->count(); ++i)
    {
        if(list->at(i)->getSocketDescriptor() == socketDescriptor)
        {
            //list->at(i)->disconnectSocket();
            list->remove(i);
            break;
        }
    }

    QVector<WaiterName*>* q = &GlobalData::waiter;

    for (int i = 0; i < q->count(); ++i)
    {
        if(q->at(i)->ID == socketDescriptor)
        {
            q->remove(i);
        }
    }

    if(isKitchenSocket())
    {
        connectedKitchen--;
        if(connectedKitchen == 0)
        {
            isKitchenConnected = false;
        }
    }

    emit addItemInServerManagement();
    //socket->deleteLater();
    //exit(0);
}

bool MyTcpSocket::isKitchenSocket()
{
    return isKitchen;
}

//QSqlQuery *MyTcpSocket::execute(QString cmdstr)
//{
//    QSqlDatabase &database = databaseCon::getDatabase();
//    database = (!QSqlDatabase::contains()) ? QSqlDatabase::addDatabase("QSQLITE") : QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false) ;
//    QSqlQuery* q = new QSqlQuery(database);
//    qDebug() << "MyTcpSocket.cpp (execute) : DatabaseName : " << database.databaseName() ;
//    if(q->exec(cmdstr))
//    {
//        qDebug() << "MyTcpSocket.cpp (execute) : execute : " << cmdstr ;
//        return q;
//    }
//    qDebug() << "MyTcpSocket.cpp (execute) : not execute : " << cmdstr ;
//    qDebug() << "MyTcpSocket.cpp (execute) :" << q->lastError().databaseText();
//    return q;
//}

QString MyTcpSocket::getClientName() const
{
    return clientName;
}

void MyTcpSocket::sendToKitchenChildThread(qint16 orderNo,qint16 tblNo,QString name )
{
    if(!isKitchen)
    {
        qDebug() << "MyTcpSocket (sendToKitchen) : not kitchen : " << clientName;
        return;
    }
    qDebug() << "MyTcpSocket (sendToKitchen) : sending msg to kitchen : " << orderNo;
    qDebug() << "MyTcpSocket (sendToKitchen) : sending msg to kitchen : " << tblNo;
    qDebug() << "MyTcpSocket (sendToKitchen) : is this kitchen thread : " << isKitchenSocket();

    QByteArray dataOut;
    QDataStream out(&dataOut,QIODevice::ReadWrite);

    databaseCon d;

    QString cmd = "SELECT a.*,b.itemName FROM oderDataFromWaiter a LEFT JOIN mstTblMenu b ON a.Item_id = b.id WHERE orderID = "+QString::number(orderNo)+"" ;
    QSqlQuery* q = d.execute(cmd) ;

    //QSqlQuery* q = runSqlQuery(cmd);

    qint16 action = ALLAction::individual;
    qint16 count = 0 ;
    //QString ordertype = "Booked Table";

    for( ; q->next() ; ++count);
    q->seek(-1);

    out << action ;
    out << orderNo;
    out << name;
    out << tblNo;
    out << count;

    qDebug() << "MyTcpSocket (sendToKitchen) : count of total Item: " << count;

    enum column{i_id,iqty,itblNumber,istatus,inote,iorderID,Billid,iName};

    while(q->next())
    {
        QString itemName = q->value(iName).toString();
        QString note = q->value(inote).toString();
        double qty = q->value(iqty).toDouble();

        qDebug() << "MyTcpSocket (sendToKitchen) : name : " << itemName;
        qDebug() << "MyTcpSocket (sendToKitchen) : qty : " << qty;
        qDebug() << "MyTcpSocket (sendToKitchen) : qty : " << note;

        out << itemName << qty << note;
    }

    int sendBytes = socket->write(dataOut);
    socket->flush();
    qDebug() << "MyTcpSocket (sendToKitchen) : size of send data : " << sendBytes;
    delete q;
}

void MyTcpSocket::deleteOrderFromKitchen(qint16 orderNo)
{
    if(!isKitchen)
    {
        qDebug() << "MyTcpSocket (deleteOrderFromKitchen) : not kitchen : " << clientName;
        return;
    }

    QByteArray dataOut;
    QDataStream out(&dataOut,QIODevice::ReadWrite);

    qint16 action = ALLAction::deleteOrder;

    out << action << orderNo;

    socket->write(dataOut);
    socket->flush();
    qDebug() << "MyTcpSocket (deleteOrderFromKitchen) : data to send : " << dataOut;

}

bool MyTcpSocket::getIsKitchenConnected()
{
    return isKitchenConnected;
}

QSqlQuery *MyTcpSocket::runSqlQuery(QString cmd)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString constr = XmlManipulation::getData("Database","PATH");

    database.setDatabaseName(constr);

    QSqlQuery* q = new QSqlQuery(database);

    if(!database.isOpen())
    {
        if (!database.open())
        {
            qDebug() << "MyTcpSocket.cpp (runSqlQuery) : not connected";
        }
        else
        {
            qDebug() << "MyTcpSocket.cpp (runSqlQuery) : connected";


            qDebug() << "MyTcpSocket.cpp (runSqlQuery) : DatabaseName : " << database.databaseName() ;

            QString PROGMA = "PRAGMA foreign_keys = ON;";

            if(q->exec(PROGMA))
            {
                qDebug() << "MyTcpSocket.cpp (runSqlQuery) : execute : " << PROGMA ;
            }
            else
            {
                qDebug() << "MyTcpSocket.cpp (runSqlQuery) : not execute : " << PROGMA ;
            }
            if(q->exec(cmd))
            {
                qDebug() << "MyTcpSocket.cpp (runSqlQuery) : execute : " << cmd ;
                return q;
            }
            qDebug() << "MyTcpSocket.cpp (runSqlQuery) : not execute : " << cmd ;
            qDebug() << "MyTcpSocket.cpp (runSqlQuery) :" << q->lastError().databaseText();
            return q;

            //delete this->execute("PRAGMA foreign_keys = ON;");
        }
    }
    return q;
}

qintptr MyTcpSocket::getSocketDescriptor() const
{
    return socketDescriptor;
}

void MyTcpSocket::disconnectSocket()
{
    socket->disconnectFromHost();
    //exit(0);
}
