#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QVector>
#include "customWidgets/itemwidget.h"

namespace Ui {
class AdminWidget;
}

class AdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = nullptr);
    void loadData();
    void deleteVecterData();

    ~AdminWidget();

private slots:
    void on_AddItem_clicked();

private:
    Ui::AdminWidget *ui;
    QVector<ItemWidget*> itemlist;
};

#endif // ADMINWIDGET_H
