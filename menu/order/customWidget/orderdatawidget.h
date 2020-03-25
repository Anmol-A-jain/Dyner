#ifndef ORDERDATAWIDGET_H
#define ORDERDATAWIDGET_H

#include <QWidget>
#include "nestedCustomWidget/statusorderitem.h"


namespace Ui {
class orderDataWidget;
}

class orderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit orderDataWidget(int orderNo,QWidget *parent = nullptr);
    ~orderDataWidget();
    void deleteVectorData();

private:
    Ui::orderDataWidget *ui;
    QWidget* myParent;
    int orderNo;

    QVector<statusOrderItem*> list;
};

#endif // ORDERDATAWIDGET_H
