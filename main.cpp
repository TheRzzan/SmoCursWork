#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Morozov::Controller controller = Morozov::Controller();
    controller.setAlpha(500);
    controller.setBeta(2);
    controller.setLambda(2);
    controller.setSourcesAmount(10);
    controller.setBuffersAmount(2);
    controller.setDevicesAmount(3);
    controller.setRequestsNumber(30);

    w.setController(controller);
    w.show();

    return a.exec();
}
