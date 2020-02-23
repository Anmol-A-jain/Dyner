#ifndef PAYMENTMATHOD_H
#define PAYMENTMATHOD_H

#include <QDialog>

namespace Ui {
class paymentMathod;
}

class paymentMathod : public QDialog
{
    Q_OBJECT

public:
    explicit paymentMathod(QWidget *parent = nullptr);
    ~paymentMathod();

private:
    Ui::paymentMathod *ui;
};

#endif // PAYMENTMATHOD_H
