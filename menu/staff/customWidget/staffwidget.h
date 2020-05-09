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

    void setData(QString id,QString name,QString username,QString designation,QString salary,QString mblno,QString address,QString city);
    ~staffwidget();

private slots:
    void on_editbtn_clicked();

    void on_deletebtn_clicked();

private:
    Ui::staffwidget *ui;
    QWidget* myParent;
};

#endif // STAFFWIDGET_H
