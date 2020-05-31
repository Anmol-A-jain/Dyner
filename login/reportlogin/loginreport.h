#ifndef LOGINREPORT_H
#define LOGINREPORT_H

#include <QWidget>
#include <QVector>
#include "customwidget/report.h"


namespace Ui {
class LoginReport;
}

class LoginReport : public QWidget
{
    Q_OBJECT

public:
    explicit LoginReport(QWidget *parent = nullptr);

    ~LoginReport();
    void SelectionChange();
    void deleteVectorData();

private slots:
    void on_rdbToday_clicked();

    void on_rdbWeekly_clicked();

    void on_rdbFromToDate_clicked();

    void on_btnSearch_clicked();

private:
    Ui::LoginReport *ui;
    QVector<report*> list;
};

#endif // LOGINREPORT_H
