#ifndef SERVERMANAGEMENT_H
#define SERVERMANAGEMENT_H

#include <QWidget>
#include "customWidget/waiterinformation.h"

namespace Ui {
class ServerManagement;
}

class ServerManagement : public QWidget
{
    Q_OBJECT

public:
    explicit ServerManagement(QWidget *parent = nullptr);
    ~ServerManagement();
    void loadData();
    void deleteVectordata();
    void removeData(qintptr id);
    void addDevice(qintptr id);

private slots:
    void on_btnDisconnect_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::ServerManagement *ui;
    QVector<WaiterInformation*> list;
};

#endif // SERVERMANAGEMENT_H
