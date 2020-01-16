#ifndef BILLHISTORYWIDGET_H
#define BILLHISTORYWIDGET_H

#include <QWidget>

namespace Ui {
class BillHistoryWidget;
}

class BillHistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BillHistoryWidget(QWidget *parent = nullptr);
    ~BillHistoryWidget();

private:
    Ui::BillHistoryWidget *ui;
};

#endif // BILLHISTORYWIDGET_H
