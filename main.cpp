#include <QCoreApplication>

#include "win.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    win w;
    w.start();

    return a.exec();
}
