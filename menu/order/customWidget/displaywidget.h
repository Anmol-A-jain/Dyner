#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H
// display data for header/menu/orderWidget

#include <QWidget>

namespace Ui {
class displayWidget;
}

class displayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit displayWidget(QString idString,QString name, QString category, double Qty, double price, int tblNo ,QWidget *parent = nullptr);
    ~displayWidget();
    double getTotal();

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::displayWidget *ui;
    QString idString,id,name,category;
    double Qty,price,amt;
    QWidget* myparent;
    int tblNo;
};

#endif // DISPLAYWIDGET_H
