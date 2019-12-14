#ifndef MENUBUTTONS_H
#define MENUBUTTONS_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "ui_dyner.h"

namespace Ui {
class menuButtons;
}

class menuButtons : public QWidget
{
    Q_OBJECT

public:
    explicit menuButtons(QWidget *parent = nullptr);
    ~menuButtons();
    void setShadow(QWidget* widget, QColor color);

private slots:
    void on_btnOrder_clicked();

    void on_btnBillHistory_clicked();

    void on_btnBillReq_clicked();

    void on_btnAdmin_clicked();

private:
    void showMenuAndDeleteThis(int option);
    Ui::menuButtons *ui;
    QWidget* parentName;
};

#endif // MENUBUTTONS_H
