#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setController(const Morozov::Controller &value);

private slots:
    void on_buttonModulate_clicked();

    void on_buttonNext_clicked();

    void on_buttonBack_clicked();

private:
    Ui::MainWindow *ui;
    Morozov::Controller controller;
    Morozov::Analytics analytics;
    int step = 0;
    std::list<std::string> resultsList;
    int currentRes;
};

#endif // MAINWINDOW_H
