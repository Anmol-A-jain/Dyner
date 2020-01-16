#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = nullptr);
    //setting data to id, name, category, price
    void setData(QString id,QString name,QString category,QString price);
    ~ItemWidget();

private slots:
    void on_editbtn_clicked();

    void on_deletebtn_clicked();

private:
    Ui::ItemWidget *ui;
    QWidget* myParent;
};

#endif // ITEMWIDGET_H
