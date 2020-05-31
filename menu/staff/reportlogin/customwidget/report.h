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
    explicit report(QWidget *parent = nullptr);
    ~report();

private:
    Ui::report *ui;
};

#endif // REPORT_H
