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
}

bool Morozov::Device::isFreeDevice()
{
    return devices.size() != size;
}

int Morozov::Device::addNewRequest(float currentTime, Morozov::Request request)
{
    float timeToDo = currentTime + (std::log(qrand() + 1) - std::log(RAND_MAX)/(-this->lambda));
    devices.push_front(std::make_pair(timeToDo, request));
    return devices.size();
}

std::list<std::pair<float, int> > Morozov::Device::freeDoneDevices(float currentTime)
{
    std::list<std::pair<float, int>> tmpList;
    std::list<std::pair<float, Request>> tmpList2;

    int i = 1;
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        if ((*it).first < currentTime) {
            tmpList.push_back(std::make_pair((*it).first, i));
        } else {
            tmpList2.push_back(*it);
        }
        i++;
    }
    devices.clear();
    devices.insert(devices.end(), tmpList2.begin(), tmpList2.end());

    return tmpList;
}
