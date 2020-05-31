#include "dyner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    a.setWindowIcon(QIcon(":/img/img/icon1.png"));
    a.setStyleSheet("font-size:30px;");
    Dyner w;
    w.show();
    return a.exec();
}
