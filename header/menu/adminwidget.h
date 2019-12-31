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
    void loadInfo();
    void deleteVecterData();

    ~AdminWidget();

private slots:
    void on_AddItem_clicked();

    void on_editButton_clicked();

    void on_SearchButton_clicked();

    void on_SearchTextBox_returnPressed();

    void on_SearchTextBox_textChanged(const QString &arg1);

    void on_btnEditCategory_clicked();

private:
    Ui::AdminWidget *ui;
    QVector<ItemWidget*> itemlist;
};

#endif // ADMINWIDGET_H
