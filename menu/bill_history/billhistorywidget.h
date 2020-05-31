#ifndef BILLHISTORYWIDGET_H
#define BILLHISTORYWIDGET_H

#include <QWidget>
#include <QVector>
#include "customWidget/history.h"

namespace Ui {
class BillHistoryWidget;
}

class BillHistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BillHistoryWidget(QWidget *parent = nullptr);
    ~BillHistoryWidget();
    void SelectionChange();
    void deleteVectorData();
<<<<<<< HEAD
=======
     void updateTotalSales();
     void resetTotalSales();
>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6

private slots:
    void on_rdbToday_clicked();

<<<<<<< HEAD
    void on_rdbYesterday_clicked();

    void on_rdbWeekly_clicked();

    void on_rdb15Day_clicked();

    void on_rdbMonthly_clicked();

=======
    void on_rdbWeekly_clicked();

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
    void on_rdbFromToDate_clicked();

    void on_btnSearch_clicked();

private:
    Ui::BillHistoryWidget *ui;
    QVector<History*> list;
<<<<<<< HEAD
=======

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
};

#endif // BILLHISTORYWIDGET_H
