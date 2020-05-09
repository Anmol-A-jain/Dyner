#ifndef STAFF_H
#define STAFF_H

#include <QWidget>
#include <QVector>
#include "customWidget/staffwidget.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSpacerItem>

namespace Ui {
class staff;
}

class staff : public QWidget
{
    Q_OBJECT

public:
    explicit staff(QWidget *parent = nullptr);

   void loadData();

    void deleteVecterData();
    void paintEvent(QPaintEvent *event) override;
    void loadComboBoxData();
     void btnAddDesignationClicked();

    ~staff();

private slots:
    void on_btnAddDesignation_clicked();

    void on_btnLoginReport_clicked();

    void on_btnAddEmp_clicked();

    void on_DesignationList_currentIndexChanged(int index);

    void on_menuColumn_currentIndexChanged(int index);

    void on_SearchTextBox_textChanged(const QString &arg1);

    void on_SearchTextBox_returnPressed();

    void on_SearchButton_clicked();

private:
    Ui::staff *ui;
    QVector<staffwidget*> stafflist;
};

#endif // STAFF_H
