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

void MainWindow::setSource(Morozov::Source value)
{
    this->source = &value;
}

void MainWindow::on_buttonNext_clicked()
{
    Morozov::Request request = this->source->getNextRequest();

    std::string str1 = std::to_string(request.getSourceId()) + "." + std::to_string(request.getRequestNumber());
    ui->textRequestName->setText(QString::fromUtf8(str1.c_str()));

    std::string str2 = std::to_string(request.getTimeOfWait());
    ui->texrTimeOfWait->setText(QString::fromUtf8(str2.c_str()));
}
