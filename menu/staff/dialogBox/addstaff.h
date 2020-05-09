#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QDialog>
#include <QAbstractButton>

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

private:
    Ui::addStaff *ui;
    QWidget* myParent;
};

#endif // ADDSTAFF_H
