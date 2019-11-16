#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Morozov::Controller controller = Morozov::Controller();
    controller.setAlpha(300);
    controller.setBeta(2);
    controller.setLambda(2);
    controller.setSourcesAmount(16);
    controller.setBuffersAmount(2);
    controller.setDevicesAmount(2);
    controller.setRequestsNumber(4000);

    w.setController(controller);
    w.show();

    return a.exec();
}
