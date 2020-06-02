#ifndef STAFFROW_H
#define STAFFROW_H

#include <QWidget>

namespace Ui {
class StaffRow;
}

class StaffRow : public QWidget
{
    Q_OBJECT

public:
    explicit StaffRow(QWidget *parent = nullptr);
    ~StaffRow();

    void setData(QString ID,QString name,QString designation,QString password);

private slots:
    void on_showPass_clicked();

    void on_editbtn_clicked();

    void on_deletebtn_clicked();

private:
    Ui::StaffRow *ui;
    QWidget* myParent;
    bool isEditModeOn;
};

#endif // STAFFROW_H
