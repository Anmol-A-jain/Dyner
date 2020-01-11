#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class displayWidget;
}

class displayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit displayWidget(QWidget *parent = nullptr);
    ~displayWidget();

private:
    Ui::displayWidget *ui;
};

#endif // DISPLAYWIDGET_H
