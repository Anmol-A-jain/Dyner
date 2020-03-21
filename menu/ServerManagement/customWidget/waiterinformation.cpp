#include "waiterinformation.h"
#include "ui_waiterinformation.h"
#include "server/dynerserver.h"
#include "../servermanagement.h"
#include "QMessageBox"
#include "data/globaldata.h"


WaiterInformation::WaiterInformation(qintptr id,QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaiterInformation)
{
    ui->setupUi(this);

    this->myParent = parent;

    ui->lblId->setText(QString::number(id));
    ui->lblName->setText(name);

    this->name = name;
    this->id = id;

    GlobalData::setShadow(ui->btnDisconnect,QColor(255,0,0),0,10);
    GlobalData::setShadow(this,QColor(0,0,0),0,10);

}

WaiterInformation::~WaiterInformation()
{
    delete ui;
}

int WaiterInformation::getId()
{
    return ui->lblId->text().toUInt();
}

void WaiterInformation::on_btnDisconnect_clicked()
{
    int reply = QMessageBox::warning(this,"Disconnected","Do you want to Disconnect " + this->name + "("+QString::number(this->id)+")",QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No,QMessageBox::StandardButton::No);
    if(reply == QMessageBox::StandardButton::No)
    {
        return;
    }

    QVector<MyTcpSocket *>* clientlist = DynerServer::getClientlist();

    for (int i = 0; i < clientlist->count(); ++i)
    {
        int id =clientlist->at(i)->getSocketDescriptor();
        if(id == ui->lblId->text().toInt())
        {
            if(clientlist->at(i) != nullptr)
            {
                qDebug() << "WaiterInformation (on_btnDisconnect_clicked) : nullptr at " << i;
                return;
            }
            clientlist->at(i)->disconnectSocket();
            clientlist->remove(i);
            static_cast<ServerManagement*>(myParent)->removeData(id);
            return;
        }
    }
}
