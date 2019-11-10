#include "device.h"
#include <algorithm>
#include <QApplication>
#include <math.h>

Morozov::Device::Device()
{
    this->size = 0;
    this->lambda = 0;
}

Morozov::Device::Device(int size, float lambda)
{
    this->size = size;
    this->lambda = lambda;
    for (int i = 0; i < size; i++) {
        devices.push_back(nullptr);
    }
}

bool Morozov::Device::isFreeDevice()
{
    bool res = false;
    for (int i = 0; i < size; i++) {
        if (devices.at(i) == nullptr)
            res = true;
    }
    return res;
}

int Morozov::Device::addNewRequest(float currentTime, Morozov::Request request)
{
    float timeToDo = currentTime + (std::log(qrand() + 1) - std::log(RAND_MAX)/(-this->lambda));

    for (int i = 0; i < size; i++) {
        if (devices.at(i) == nullptr) {
            devices.at(i) = new std::pair<float, Request>(timeToDo, Request(request.getTimeOfWait(), request.getSourceId(), request.getRequestNumber()));
            return i + 1;
        }
    }

    return -1;
}

std::list<std::pair<float, int> > Morozov::Device::freeDoneDevices(float currentTime)
{
    std::list<std::pair<float, int>> tmpList;
    std::vector<std::pair<float, Request> *> devicesTmp;

    for (int i = 0; i < size; i++) {
        if (devices.at(i) != nullptr) {
            if ((*devices.at(i)).first < currentTime) {
                tmpList.push_back(std::make_pair((*devices.at(i)).first, i + 1));
                devicesTmp.push_back(nullptr);
            } else {
                devicesTmp.push_back(devices.at(i));
            }
        } else {
            devicesTmp.push_back(nullptr);
        }
        i++;
    }

    devices = devicesTmp;

    return tmpList;
}
