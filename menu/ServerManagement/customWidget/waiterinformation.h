#ifndef WAITERINFORMATION_H
#define WAITERINFORMATION_H

#include <QWidget>

namespace Ui {
class WaiterInformation;
}

class WaiterInformation : public QWidget
{
    Q_OBJECT

public:
    explicit WaiterInformation(qintptr id,QString name, QWidget *parent = nullptr);
    ~WaiterInformation();
    int getId();

private slots:

    void on_btnDisconnect_clicked();

private:
    Ui::WaiterInformation *ui;
    QWidget* myParent;

    QString name;
    qintptr id;
};

#endif // WAITERINFORMATION_H
