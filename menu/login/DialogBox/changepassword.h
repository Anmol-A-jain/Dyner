#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(bool isOldPassrequired = true,QWidget *parent = nullptr);
    ~ChangePassword();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::ChangePassword *ui;
    bool isOldPassrequired;
};

#endif // CHANGEPASSWORD_H
