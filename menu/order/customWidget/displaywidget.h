#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H
// display data for header/menu/orderWidget

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>

namespace Ui {
class displayWidget;
}

struct OrderData
{
    QLabel* id;
    QLabel* name;
    QLabel* category;
    QDoubleSpinBox* qty;
    QLabel* price;
};

class displayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit displayWidget(QString idString,QString name, QString category, double Qty, double price, int tblNo ,QWidget *parent = nullptr);
    ~displayWidget();
    double getTotal();
    void setFlag(bool flag);
    struct OrderData getData();

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

    void on_btnDelete_clicked();

private:
    Ui::displayWidget *ui;

    double amt;
    QWidget* myparent;
    int tblNo;
    bool flag;
    struct OrderData orderData;
};

#endif // DISPLAYWIDGET_H
