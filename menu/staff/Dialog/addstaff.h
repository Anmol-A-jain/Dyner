#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QDialog>

namespace Ui {
class addStaff;
}

class addStaff : public QDialog
{
    Q_OBJECT

public:
    explicit addStaff(QWidget *parent = nullptr);
    ~addStaff();

private slots:
    void on_btnAdd_clicked();

    void on_buttonBox_rejected();

private:
    Ui::addStaff *ui;
    QWidget* myParent;
};

#endif // ADDSTAFF_H
