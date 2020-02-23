#ifndef PAYMENTMATHOD_H
#define PAYMENTMATHOD_H

#include <QDialog>
#include <QVector>
#include "../customWidget/displaywidget.h"

namespace Ui {
class paymentMathod;
}

class paymentMathod : public QDialog
{
    Q_OBJECT

public:
    explicit paymentMathod(double netamt,double discount,double tax,int tblno,QString custno,QString ordertype,QString custnm,QVector<displayWidget*> list,QWidget *parent = nullptr);
    ~paymentMathod();
    void insertData(QString paymentType);

private slots:
    void on_btnCash_clicked();

    void on_btnCard_clicked();

private:
    Ui::paymentMathod *ui;
    double netamt;
    double discount;
    double tax;
    int tblno;
    QString custno,ordertype,custnm;
    QVector<displayWidget*> list;
    QWidget* myparent;
};

#endif // PAYMENTMATHOD_H
