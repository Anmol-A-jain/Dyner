#ifndef STAFF_H
#define STAFF_H

#include <QWidget>
#include <QVector>
#include "menu/staff/customWidget/staffrow.h"

namespace Ui {
class Staff;
}

class Staff : public QWidget
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = nullptr);
    ~Staff();

    inline void loadData();
    inline void deleteVectorData();
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_AddStaff_clicked();

    void on_menuColumn_currentIndexChanged(const QString &arg1);

    void on_SearchTextBox_textChanged(const QString &arg1);

    void on_List_currentIndexChanged(const QString &arg1);

private:
    Ui::Staff *ui;
    QWidget* myParent;
    QVector<StaffRow*> list;
};

#endif // STAFF_H
