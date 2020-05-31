#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

     void log_admin();

private slots:

    void on_btnlogin_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
