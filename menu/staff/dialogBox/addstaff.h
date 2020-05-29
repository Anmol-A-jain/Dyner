#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QDialog>
#include <QAbstractButton>
#include <QRegExpValidator>

namespace Ui {
class addStaff;
}

class addStaff : public QDialog
{
    Q_OBJECT

public:
    explicit addStaff(QWidget *parent = nullptr);
    ~addStaff();
    void LoadDesignation();

private slots:
    void on_btnadd_clicked();

    void on_btnaddDesignation_clicked();

    void on_designation_currentIndexChanged(const QString &arg1);

    void on_name_textChanged(const QString &arg1);

    void on_btncancel_clicked();

private:
    Ui::addStaff *ui;
    QRegExpValidator* r1;
    QRegExpValidator* r2;
    QWidget* myParent;
};

#endif // ADDSTAFF_H
