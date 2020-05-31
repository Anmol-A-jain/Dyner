#ifndef MENUBUTTONS_H
#define MENUBUTTONS_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class menuButtons;
}

class MenuButtons : public QWidget
{
    Q_OBJECT

public:
    explicit MenuButtons(QWidget *parent = nullptr);
    void setShadow(QWidget *widget, QColor color);
    ~MenuButtons();

private slots:
    void on_btnOrder_clicked();

    void on_btnBillHistory_clicked();

    void on_btnAdmin_clicked();

    void on_btnServer_clicked();

<<<<<<< HEAD
=======
    void on_btnStaff_clicked();

    void on_btnlogin_clicked();

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6
private:
    Ui::menuButtons *ui;
    // storing parent object
    QWidget* parentName;
};

#endif // MENUBUTTONS_H
