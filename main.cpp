#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Morozov::Controller controller = Morozov::Controller();
    controller.setAlpha(100);
    controller.setBeta(2);
    controller.setLambda(2);
    controller.setSourcesAmount(10);
    controller.setBuffersAmount(2);
    controller.setDevicesAmount(1);
    controller.setRequestsNumber(1000);

    w.setController(controller);
    w.show();

    return a.exec();
}
