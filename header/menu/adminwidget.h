#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QVector>
#include "customWidgets/itemwidget.h"
#include <QScrollArea>
#include <QVBoxLayout>

namespace Ui {
class AdminWidget;
}

class AdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = nullptr);
    void loadData();
    void loadInfo();
    void deleteVecterData();
    void paintEvent(QPaintEvent *event) override;
    void loadComboBoxData();
    void btnEditCategoryClicked();

    ~AdminWidget();

private slots:
    void on_AddItem_clicked();

    void on_editButton_clicked();

    void on_SearchButton_clicked();

    void on_SearchTextBox_returnPressed();

    void on_SearchTextBox_textChanged(const QString &arg1);

    void on_btnEditCategory_clicked();

    void on_menuColumn_currentIndexChanged(int index);

    void on_categoryList_currentIndexChanged(int index);

private:
    Ui::AdminWidget *ui;
    QVector<ItemWidget*> itemlist;
    QScrollArea *scroll;
};

#endif // ADMINWIDGET_H
