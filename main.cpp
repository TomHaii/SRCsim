#include "Qt/mainwindow.h"
#include "core/src.h"
#include "core/bus.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Bus bus;
    bus.tests();

    return a.exec();
}
