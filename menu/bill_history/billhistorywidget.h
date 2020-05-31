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

private slots:
    void on_rdbToday_clicked();

    void on_rdbYesterday_clicked();

    void on_rdbWeekly_clicked();

    void on_rdb15Day_clicked();

    void on_rdbMonthly_clicked();

    void on_rdbFromToDate_clicked();

    void on_btnSearch_clicked();

private:
    Ui::BillHistoryWidget *ui;
    QVector<History*> list;
};

#endif // BILLHISTORYWIDGET_H
