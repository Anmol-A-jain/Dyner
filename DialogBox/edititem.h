#ifndef EDITITEM_H
#define EDITITEM_H

#include <QDialog>

namespace Ui {
class EditItem;
}

class EditItem : public QDialog
{
    Q_OBJECT

public:
    explicit EditItem(QString id,QString name,QString category, double price ,QWidget *parent = nullptr);
    ~EditItem();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditItem *ui;
    QWidget* myParent;
};

#endif // EDITITEM_H
