#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>
#include <QVector>
#include "customWidget/orderitemdata.h"
#include "customWidget/displaywidget.h"

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();
    int getTblNo();
    void loadData();
    void deleterVecterData();

private slots:
    void on_cmbOrrderType_currentIndexChanged(int index);

    void on_pushButton_clicked();


    void on_cmbTblNo_currentTextChanged(const QString &arg1);

    void on_cmbOrrderType_currentTextChanged(const QString &arg1);

private:
    Ui::OrderWidget *ui;
    QVector<displayWidget*> list;
};

#endif // ORDERWIDGET_H
