#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "source.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSource(Morozov::Source value);

private slots:
    void on_buttonNext_clicked();

private:
    Ui::MainWindow *ui;

    Morozov::Source *source;
};

#endif // MAINWINDOW_H
