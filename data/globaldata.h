#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

// storing waiter data came from android
struct WaiterName
{
    QString name;
    qintptr ID;
};

class GlobalData
{
public:
    GlobalData();
    QString getTagName(int tagname);
    QString getattribute(int tagname);
    enum data{QtyTable,Discount,Tax,customerNameMblNo};
<<<<<<< HEAD
=======
    enum designation{manager,assistant_manager,Waiter,chief,trainee,worker};

>>>>>>> 24f7eebdf8c0d81e98db20e676926fa1df9acbc6

    static void printBill(QString name, int billId, QString amount , QString tax, QString discount, QString finalAmount, QWidget *parent = nullptr);

    static void setShadow(QWidget* widget, QColor color = QColor(0,0,0),qreal real = 0.0,qreal radius = 10.0);


    // storing waiter data came from android
    static QVector<WaiterName*> waiter;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
