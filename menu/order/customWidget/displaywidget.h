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
    void setFlag(bool flag);

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

    void on_btnDelete_clicked();

private:
    Ui::displayWidget *ui;

    double amt;
    QWidget* myparent;
    int tblNo;
    bool flag;
};

#endif // DISPLAYWIDGET_H
