#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>

namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

public:
    explicit History(int srNo,QString billId,QString custName,QString date,QString tblNo,QString orderType,QString paymentMethod,QString discount,QString tax,QString netAmount,QWidget *parent = nullptr);
    ~History();

private slots:
    void on_btnReport_clicked();

private:
    Ui::History *ui;
};

#endif // HISTORY_H
