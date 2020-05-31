#ifndef ADDDESIGNATION_H
#define ADDDESIGNATION_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class addDesignation;
}

class addDesignation : public QDialog
{
    Q_OBJECT

public:
    explicit addDesignation(QWidget *parent = nullptr);
    void loadData();
    ~addDesignation();

private slots:

    void on_search_textChanged(const QString &arg1);

    void on_DesignationList_currentIndexChanged(const QString &arg1);//,QString &arg2

    void on_add_clicked();

    void on_remove_clicked();

    void on_update_clicked();

    void on_searchBox_textChanged(const QString &arg1);

    void on_buttonBox_rejected();

private:
    Ui::addDesignation *ui;
     QWidget* myParent;
};

#endif // ADDDESIGNATION_H
