#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();

private slots:
    void on_cmbOrrderType_currentIndexChanged(int index);

private:
    Ui::OrderWidget *ui;
};

#endif // ORDERWIDGET_H
