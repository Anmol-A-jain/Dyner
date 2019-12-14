#ifndef BILLREQWIDGET_H
#define BILLREQWIDGET_H

#include <QWidget>

namespace Ui {
class BillReqWidget;
}

class BillReqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BillReqWidget(QWidget *parent = nullptr);
    ~BillReqWidget();

private:
    Ui::BillReqWidget *ui;
};

#endif // BILLREQWIDGET_H
