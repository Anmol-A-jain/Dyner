#include "mytcpsocket.h"
#include "data/allaction.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"
#include "data/databasecon.h"

MyTcpSocket::MyTcpSocket(qintptr ID , QObject *parent )
    :QThread(parent)
{
    this->socketDescriptor = ID;
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
        connect(socket, &QTcpSocket::disconnected , this, &MyTcpSocket::myDisconnected  );

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
    QByteArray dataIn = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << dataIn;

    QDataStream in(&dataIn,QIODevice::ReadWrite);


    qint16 action;
    in >> action;

    qDebug() << socketDescriptor << " Data in: " << dataIn << ":" << action;

    qDebug() << "serverConnection (myReadReady) : action : " << action;

    switch (action)
    {
        case ALLAction::error :
        {
            qDebug() << "serverConnection (myReadReady) : list : " << dataIn;
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            //sending total table Quantity..

            QByteArray dataOut ;

            QDataStream out(&dataOut,QIODevice::ReadWrite);

            GlobalData g;
            qint16 tblNo =  XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) ).toInt();
            qint16 i = ALLAction::getTotaltableNo;

            //sending action and total table no
            out << i;
            out << tblNo;

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            int size = socket->write(dataOut);
            socket->flush();

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg size : " << size ;

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

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            socket->write(dataOut);
            socket->flush();

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

            QString name =  XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(tblNo),list.at(0));
            QString mblNo =  XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(tblNo),list.at(1));
            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : customer data : " << name <<":"<< mblNo ;

            qint16 i = ALLAction::getCustInfo;
            out << i << name << mblNo;

            qDebug() << "serverConnection (myReadReady) : ALLAction::getTotaltableNo : sending msg : " << dataOut ;
            socket->write(dataOut);
            socket->flush();
            break;
        }
        case ALLAction::cartData :
        {
            int tblNo = -1,count = 0 ;
            in >> tblNo >> count;

            qDebug() << "serverConnection (myReadReady) : ALLAction::cartData : table no : " << tblNo;
            qDebug() << "serverConnection (myReadReady) : ALLAction::cartData : total item : " << count;

            for (int i = 0; i < count; ++i)
            {
                QString id;
                double qty;
                in >> id >> qty;
                qDebug() << "serverConnection (myReadReady) : ALLAction::cartData : item id : " << id;
                qDebug() << "serverConnection (myReadReady) : ALLAction::cartData : item qty : " << qty;
                double preQty = 0;

                ItemData* item = new ItemData;
                item->id = id;
                item->qty = qty;

                CartData* cart = new CartData;
                cart->tblNO = tblNo;
                cart->item = item;

                currentOrder.push_back(cart);

                databaseCon d;
                QString cmd = "select * from tblTempOrder WHERE table_no =" + QString::number(tblNo) +" AND item_id = " + id;
                QSqlQuery* q = d.execute(cmd);

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
            break;
        }
        default:
        {
            qDebug() << "serverConnection (myReadReady) : default case called : " << dataIn;
        }
    }

    // will write on server side window*/
}

void MyTcpSocket::myDisconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

QByteArray MyTcpSocket::setAction(int action, QString msg)
{
    QByteArray data = QByteArray::number(action) + "~" ;
    data.append(msg);
    return data;
}

void MyTcpSocket::disconnectSocket()
{
    socket->disconnectFromHost();
    exit(0);
}
