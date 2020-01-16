#ifndef EDITTABLENOANDDISCOUNT_H
#define EDITTABLENOANDDISCOUNT_H

#include <QDialog>

namespace Ui {
class EditTableNoAndDiscount;
}

class EditTableNoAndDiscount : public QDialog
{
    Q_OBJECT

public:
    explicit EditTableNoAndDiscount(QWidget *parent = nullptr);
    ~EditTableNoAndDiscount();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditTableNoAndDiscount *ui;
};

#endif // EDITTABLENOANDDISCOUNT_H
