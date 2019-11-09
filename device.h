#ifndef DEVICE_H
#define DEVICE_H

#include <list>
#include <utility>
#include "request.h"

namespace Morozov{
class Device
{
public:
    Device();
    Device(int size, float lambda);

    bool isFreeDevice();

    int addNewRequest(float currentTime, Request request);
    std::list<std::pair<float, int>> freeDoneDevices(float currentTime);
private:
    int size;
    float lambda;

    std::list<std::pair<float, Request>> devices;
};
}

#endif // DEVICE_H