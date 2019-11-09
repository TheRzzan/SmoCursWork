#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setController(const Morozov::Controller &value)
{
    controller = value;
}

void MainWindow::on_buttonModulate_clicked()
{
    resultsList.clear();
    std::list<std::string> resLst = controller.modulateWork();
    resultsList.insert(resultsList.end(), resLst.begin(), resLst.end());
    currentRes = 0;
}

void MainWindow::on_buttonNext_clicked()
{
    if (resultsList.size() > 0) {
        ui->textBrowser->setText(QString::fromUtf8(resultsList.front().c_str()));
        resultsList.pop_front();
    } else {
        ui->textBrowser->setText(QString::fromUtf8("Конец"));
    }
}
