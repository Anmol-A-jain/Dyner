#ifndef LOGINREPORT_H
#define LOGINREPORT_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class LoginReport;
}

class LoginReport : public QDialog
{
    Q_OBJECT

public:
    explicit LoginReport(QWidget *parent = nullptr);
    ~LoginReport();

private:
    Ui::LoginReport *ui;
};

#endif // LOGINREPORT_H
