#ifndef EDITCATEGORY_H
#define EDITCATEGORY_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class EditCategory;
}

class EditCategory : public QDialog
{
    Q_OBJECT

public:
    explicit EditCategory(QWidget *parent = nullptr);
    void loadData();
    ~EditCategory();


private slots:
    void on_add_clicked();

    void on_CategoryList_currentIndexChanged(const QString &arg1);

    void on_searchBox_textChanged(const QString &arg1);

    void on_remove_clicked();

    void on_update_clicked();

private:
    Ui::EditCategory *ui;
};

#endif // EDITCATEGORY_H
