#include "dyner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("font-size:30px;");
    Dyner w;
    w.show();
    return a.exec();
}
