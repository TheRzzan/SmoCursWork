#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setSource(Morozov::Source(500, 2, 3));
    w.show();

    return a.exec();
}
