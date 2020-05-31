#ifndef ORDERDATARECORD_H
#define ORDERDATARECORD_H

#include <QWidget>

namespace Ui {
class orderDataRecord;
}

class orderDataRecord : public QWidget
{
    Q_OBJECT

public:
    explicit orderDataRecord(QString id, QString name, QString category, QString qty, QString price, QWidget *parent = nullptr);
    ~orderDataRecord();

private:
    Ui::orderDataRecord *ui;
};

#endif // ORDERDATARECORD_H
