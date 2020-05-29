#ifndef REPORT_H
#define REPORT_H

#include <QWidget>

namespace Ui {
class report;
}

class report : public QWidget
{
    Q_OBJECT

public:
    explicit report(int srNo,QString staffId,QString userName,QString desig,QString module,QString date,QString entry,QWidget *parent = nullptr);
    ~report();

private:
    Ui::report *ui;
};

#endif // REPORT_H
