#ifndef DYNER_H
#define DYNER_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDir>
#include <QFile>
#include "server/dynerserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dyner; }
QT_END_NAMESPACE



class Dyner : public QMainWindow
{
    Q_OBJECT

public:
    Dyner(QWidget *parent = nullptr);
    QWidget* newFrame(int option); // creates new widget and returns it
    void loadWidgetWindow(int option); // show and hide menu button
    void orderButtonClick(); // emits order button
    void billHistoryButtonClick(); // emits bill history button
    void adminButtonClick(); // emits admin button
    void serverButtonClick(); // emits server button
    void homeWidget();
    void staffButtonClick();
    void setShadow(QWidget *widget, QColor color); // setting shadow to widget and formating widget title
    void closeEvent(QCloseEvent *event) override;

    void sendToDataKitchen(qint16 orderNo, qint16 tblNo, QString name);
    void serverSideAddItem();

    ~Dyner();
    static DynerServer *getServer();

    static QWidget* childFrame; // to track wich widget is currently in windowContainer

    enum buttonName{home,order,billHistory,admin,serverManagement,login,staff}; // enum for buttons

private slots:
    void on_parentButtonOrder_clicked();

    void on_parentButtonBillHistory_clicked();

    void on_parentButtonAdmin_clicked();

    void on_menuButton_clicked();

    void on_parentButtonHome_clicked();

    void on_parentButtonManagement_clicked();

    void on_btnLogout_clicked();

    void on_parentButtonStaff_clicked();

private:
    Ui::Dyner *ui;
    bool isMenuHidden; // track if menu is hidden or not
    QPushButton* currentShaddowEffect; // to track which button have currently shadow effect
    static DynerServer* server; // creating server object
    QWidget* serverWindow;
    QWidget* menuWindow;
    QWidget* orderWindow;
    QWidget* historyWindow;
    QWidget* adminWindow;
    QWidget* loginWindow;
    QWidget* staffWidget;

};
#endif // DYNER_H
