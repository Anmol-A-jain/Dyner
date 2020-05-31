#ifndef STAFFWIDGET_H
#define STAFFWIDGET_H

#include <QWidget>

namespace Ui {
class staffwidget;
}

class staffwidget : public QWidget
{
    Q_OBJECT

public:
    explicit staffwidget(QWidget *parent = nullptr);

    void setData(int sr,QString id,QString name,QString username,QString designation,QString salary,QString mblno,QString address,QString city,QString dob,QString doj);
    ~staffwidget();
//QString dob,,QString doj
    double getTotal();

private slots:
    void on_editbtn_clicked();

    void on_deletebtn_clicked();

private:
    Ui::staffwidget *ui;
    QWidget* myParent;
};

#endif // STAFFWIDGET_H
