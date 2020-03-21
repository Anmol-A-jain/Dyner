#include "servermanagement.h"
#include "ui_servermanagement.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include "data/globaldata.h"
#include "server/dynerserver.h"
#include "QMessageBox"
#include <QDebug>


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

    GlobalData::setShadow(ui->btnRefresh,QColor(255,0,0),0,10);
}

ServerManagement::~ServerManagement()
{
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

void ServerManagement::on_btnRefresh_clicked()
{
    loadData();
}
