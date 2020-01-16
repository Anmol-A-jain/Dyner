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
    explicit displayWidget(QString id,QString name, QString category, int Qty, double rate ,QWidget *parent = nullptr);
    ~displayWidget();

private:
    Ui::displayWidget *ui;
};

#endif // DISPLAYWIDGET_H
