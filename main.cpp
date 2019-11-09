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
    controller.setSourcesAmount(2);
    controller.setBuffersAmount(1);
    controller.setDevicesAmount(1);
    controller.setRequestsNumber(10);

    w.setController(controller);
    w.show();

    return a.exec();
}
