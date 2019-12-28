#ifndef DYNER_H
#define DYNER_H

#include <QMainWindow>
#include <QHBoxLayout>


#include "header/menu/adminwidget.h"
#include "header/menu/billhistorywidget.h"
#include "header/menu/billreqwidget.h"
#include "header/menu/orderwidget.h"
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
    Ui::Dyner* getUi();
    QHBoxLayout* getFrame();
    QWidget* newFrame(int option);
    void showMenuAndDeleteThis(int option);
    void orderButtonClick();
    void billHistoryButtonClick();
    void billReqButtonClick();
    void adminButtonClick();
    void setShadow(QWidget *widget, QColor color);
    void setXml(QString xmlFile, QString DBFile);

    ~Dyner();
private slots:
    void on_parentButtonOrder_clicked();

    void on_parentButtonBillHistory_clicked();

    void on_parentButtonBillRequest_clicked();

    void on_parentButtonAdmin_clicked();

    void on_menuButton_clicked();

    void on_parentButtonHome_clicked();

private:
    Ui::Dyner *ui;
    QWidget* childFrame;
    QWidget* menuButtons;
    enum buttonName{home,order,billHistory,billReq,admin};
    bool isMenuHidden;
    QPushButton* currentShaddowEffect;
    DynerServer server;

};
#endif // DYNER_H
