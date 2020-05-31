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

<<<<<<< HEAD
=======
    double getTotal();

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
private slots:
    void on_btnReport_clicked();

private:
    Ui::History *ui;
<<<<<<< HEAD
=======

    QWidget* myparent;
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
};

#endif // HISTORY_H
