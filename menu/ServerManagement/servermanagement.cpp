#include "servermanagement.h"
#include "ui_servermanagement.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include "data/globaldata.h"
#include "server/dynerserver.h"
#include "QMessageBox"
#include <QDebug>
#include "dyner.h"

ServerManagement::ServerManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerManagement)
{
    ui->setupUi(this);
    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            ui->lblIp->setText(ui->lblIp->text().append(address.toString()));
        }
    }
    this->loadData();

    QString status = (Dyner::getServer()->isListening()) ? "On" : "off";

    ui->lblServerStatus->setText(ui->lblServerStatus->text().append(status));

    GlobalData::setShadow(ui->btnDisconnect,QColor(255,0,0),0,10);
    GlobalData::setShadow(ui->btnRefresh,QColor(67, 134, 244),0,10);
}

ServerManagement::~ServerManagement()
{
    deleteVectordata();
    delete ui;
}

void ServerManagement::loadData()
{
    this->deleteVectordata();
    static QVector<WaiterName*>* q = &GlobalData::waiter;

    for (int i = 0; i < q->count(); ++i)
    {
        WaiterInformation* waiter = new WaiterInformation(q->at(i)->ID,q->at(i)->name,this);
        ui->waiterList->addWidget(waiter);
        list.push_back(waiter);
    }
}

void ServerManagement::deleteVectordata()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

void ServerManagement::removeData(qintptr id)
{
    for (int i = 0; i < list.count(); ++i)
    {
        if(id == list.at(i)->getId())
        {
            delete list.at(i);
            list.remove(i);

            return;
        }
    }
}

void ServerManagement::on_btnDisconnect_clicked()
{
    int reply = QMessageBox::warning(this,"Disconnected All","Do you want to Disconnect All Devices",QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No,QMessageBox::StandardButton::No);
    if(reply == QMessageBox::StandardButton::No)
    {
        return;
    }

    QVector<MyTcpSocket *>* clientlist = DynerServer::getClientlist();

    qDebug() << "ServerManagement (on_btnDisconnect_clicked) : Size" << clientlist->size() ;

    int count = clientlist->count();
    for (int i = 0; i < count; ++i)
    {
        qDebug() << "ServerManagement (on_btnDisconnect_clicked) : Size" << clientlist->size() ;

        if(clientlist->at(i) == nullptr)
        {
            int id = clientlist->at(i)->getSocketDescriptor();
            qDebug() << "ServerManagement (on_btnDisconnect_clicked) : nullptr at " << i << "ID :" <<id;
            continue;
            //return;
        }
        clientlist->at(i)->disconnectSocket();
        //removeData(id);
        //return;
    }
    loadData();
}

void ServerManagement::on_btnRefresh_clicked()
{
    loadData();
}
