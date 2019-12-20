#include "header/dyner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dyner w;
    w.show();
    return a.exec();
}
