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
    explicit orderDataWidget(int orderNo, int tblNo, QWidget *grandParent = nullptr, QWidget *parent = nullptr);
    ~orderDataWidget();
    void deleteVectorData();

    QString getStatus() const;

public slots:

    void updateStatus(QString status,int orderNo);

private slots:
    void on_btnDelete_clicked();

signals:
    void refresh();

private:
    Ui::orderDataWidget *ui;
    QWidget* myParent;
    QWidget* myGrandParent;
    int orderNo;
    QVector<statusOrderItem*> list;
    QString status;
    int tblNo;
};

#endif // ORDERDATAWIDGET_H
