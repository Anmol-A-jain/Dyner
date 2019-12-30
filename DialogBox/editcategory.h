#ifndef EDITCATEGORY_H
#define EDITCATEGORY_H

#include <QDialog>

namespace Ui {
class EditCategory;
}

class EditCategory : public QDialog
{
    Q_OBJECT

public:
    explicit EditCategory(QWidget *parent = nullptr);
    ~EditCategory();

private:
    Ui::EditCategory *ui;
};

#endif // EDITCATEGORY_H
