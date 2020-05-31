#ifndef EDITSTAFF_H
#define EDITSTAFF_H

#include <QDialog>

namespace Ui {
class editStaff;
}

class editStaff : public QDialog
{
    Q_OBJECT

public:
    explicit editStaff(QString id,QString name,QString username,QString designation,double salary,QString mblno,QString address,QString city,QDate dob,QWidget *parent = nullptr);
  //QDate dob,QString doj,
    ~editStaff();

private slots:
    void on_btnUpdate_clicked();

    void on_txtDesig_currentIndexChanged(const QString &arg1);

    void on_buttonBox_rejected();

private:
    Ui::editStaff *ui;
    QWidget* myParent;
};

#endif // EDITSTAFF_H
