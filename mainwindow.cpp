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
    std::list<std::string> resLst = controller.modulateWork(analytics);
    resultsList.insert(resultsList.end(), resLst.begin(), resLst.end());
    currentRes = 0;
    step = 0;
}

void MainWindow::on_buttonNext_clicked()
{
//    if (resultsList.size() > 0) {
//        ui->textBrowser->setText(QString::fromUtf8(resultsList.front().c_str()));
//        resultsList.pop_front();
//    } else {
//        ui->textBrowser->setText(QString::fromUtf8("Конец"));
//    }


//    std::vector<Morozov::Analytics::StepModel> steps = analytics.getSteps();

//    if (step >= steps.size() || step < 0) {
//        ui->textBrowser->setText(QString::fromUtf8("Конец"));
//    } else {
//        Morozov::Analytics::StepModel stepTmp = steps.at(step);
//        int i = 0;
//        std::string resultStr = "";
//        int max = std::max(std::max(stepTmp.sources.size(), stepTmp.buffers.size()), stepTmp.devices.size());

//        do {
//            if (i >= stepTmp.sources.size()) {
//                resultStr += "\t";
//            } else {
//                resultStr += "source" + std::to_string(i) + " : " + stepTmp.sources.at(i) + "\t";
//            }

//            if (i >= stepTmp.buffers.size()) {
//                resultStr += "\t";
//            } else {
//                resultStr += "buffer" + std::to_string(i) + " : " + stepTmp.buffers.at(i) + "\t";
//            }

//            if (i >= stepTmp.devices.size()) {
//                resultStr += "\n";
//            } else {
//                resultStr += "device" + std::to_string(i) + " : " + stepTmp.devices.at(i) + "\n";
//            }

//            i++;
//        } while(i < max);

//        resultStr += "\n\nCanceled: ";
//        for (int j = 0; j < stepTmp.canceled.size(); j++) {
//            resultStr += stepTmp.canceled.at(j) + " ";
//        }

//        ui->textBrowser->setText(QString::fromUtf8(resultStr.c_str()));
//        step++;
//    }


    if (analytics.getReq_proc().size() > 0) {
        std::string resultStr2 = "";
        int all = 0;
        for (int i = 0; i < analytics.getReq_proc().size(); i++) {
            resultStr2 += "source" + std::to_string(i) + ": \t" +
                    std::to_string(analytics.getReq_proc().at(i)) + " " +
                    std::to_string(analytics.getReq_fail().at(i)) + " " +
                    std::to_string(analytics.getTime_of_wait().at(i)) + " " +
                    std::to_string(analytics.getTime_of_process().at(i)) + "\n";
            all += analytics.getReq_proc().at(i);
            all += analytics.getReq_fail().at(i);
        }

        resultStr2 += "All: " + std::to_string(all);

        ui->textBrowser->setText(QString::fromUtf8(resultStr2.c_str()));
    }
}
