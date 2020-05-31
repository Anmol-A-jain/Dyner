#ifndef ORDERDATA_H
#define ORDERDATA_H

#include <QDialog>
#include "../customWidget/orderdatarecord.h"

namespace Ui {
class Orderdata;
}

class Orderdata : public QDialog
{
    Q_OBJECT

public:
    explicit Orderdata(int billID, QString name, QString date, QWidget *parent = nullptr);
    ~Orderdata();

    void deleteVectorData();

private:
    Ui::Orderdata *ui;
    int billID;
    QVector<orderDataRecord*> list;
};

#endif // ORDERDATA_H
