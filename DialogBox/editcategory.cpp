#include "editcategory.h"
#include "ui_editcategory.h"

EditCategory::EditCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCategory)
{
    ui->setupUi(this);
}

EditCategory::~EditCategory()
{
    delete ui;
}
