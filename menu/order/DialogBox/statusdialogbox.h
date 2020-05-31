#ifndef STATUSDIALOGBOX_H
#define STATUSDIALOGBOX_H

#include <QDialog>
#include "../customWidget/orderdatawidget.h"

namespace Ui {
class StatusDialogBox;
}

class StatusDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit StatusDialogBox(int tblno,QWidget *parent = nullptr);
    ~StatusDialogBox();
    void deleteVectorData();
    void loadData();

private slots:
    void on_orderNoList_currentIndexChanged(const QString &arg1);

    void on_btnComplete_clicked();

    void refresh();

private:
    Ui::StatusDialogBox *ui;
    QWidget* myParent;
    int tblno;

    QVector<orderDataWidget*> list;
};

#endif // STATUSDIALOGBOX_H
