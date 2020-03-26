#ifndef STATUSORDERITEM_H
#define STATUSORDERITEM_H

#include <QWidget>

namespace Ui {
class statusOrderItem;
}

class statusOrderItem : public QWidget
{
    Q_OBJECT

public:
    explicit statusOrderItem(QString id, QString name, QString qty, QWidget *parent = nullptr);
    ~statusOrderItem();

    QString getId() const;

    QString getQty() const;

private:
    Ui::statusOrderItem *ui;
    QWidget* myParent;
    QString id;
    QString name;
    QString status;
    QString qty;
};

#endif // STATUSORDERITEM_H
