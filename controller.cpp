#include "controller.h"
#include "source.h"
#include "buffer.h"
#include "device.h"

Morozov::Controller::Controller()
{
    this->alpha = 0;
    this->beta = 0;
    this->lambda = 0;

    this->sourcesAmount = 0;
    this->buffersAmount = 0;
    this->devicesAmount = 0;

    this->requestsNumber = 0;
}

std::list<std::string> Morozov::Controller::modulateWork()
{
    std::list<std::string> resultList;

    Morozov::Source *sources = new Morozov::Source(alpha, beta, sourcesAmount);
    Morozov::Buffer *buffers = new Morozov::Buffer(buffersAmount);
    Morozov::Device *devices = new Morozov::Device(devicesAmount, lambda);

    float currentTime = 0;

    for (int i = 0; i < requestsNumber; i++) {
        Request nextRequest = sources->getNextRequest();
        currentTime += nextRequest.getTimeOfWait();

        std::list<std::pair<float, int> > doneRequests = devices->freeDoneDevices(currentTime);
        if (doneRequests.size() > 0) {
            for (auto it = doneRequests.begin(); it != doneRequests.end(); ++it) {
                resultList.push_back("Девайс №" + std::to_string((*it).second) + " освободился в " + std::to_string((*it).first));

                if (!buffers->isEmptyBuff()) {
                    Request request2 = buffers->getRequest();
                    int deviceNum2 = devices->addNewRequest(currentTime, request2);
                    resultList.push_back("Заявка " + std::to_string(request2.getSourceId()) + "." + std::to_string(request2.getRequestNumber())
                                         + " загружена в девайс №" + std::to_string(deviceNum2));
                }
            }
        }

        std::string tmpResStr = "Создана заявка " + std::to_string(nextRequest.getSourceId()) + "." + std::to_string(nextRequest.getRequestNumber());
        if (!devices->isFreeDevice()) {
            if (buffers->isFreeBuff()) {
                int bufferNum = buffers->addNewRequest(nextRequest);
                tmpResStr += " и загружена в буффер №" + std::to_string(bufferNum);
            } else {
                Request deletedRequest = buffers->deleteOldRequest();
                resultList.push_back("Заявка " + std::to_string(deletedRequest.getSourceId()) + "." + std::to_string(deletedRequest.getRequestNumber())
                                     + " удалена из буффера.");
                int bufferNum = buffers->addNewRequest(nextRequest);
                tmpResStr += " и загружена в буффер №" + std::to_string(bufferNum);
            }
        } else {
            int deviceNum = devices->addNewRequest(currentTime, nextRequest);
            tmpResStr += " и загружена в девайс №" + std::to_string(deviceNum);
        }

        resultList.push_back(tmpResStr);
    }

    return resultList;
}

void Morozov::Controller::setDevicesAmount(int value)
{
    devicesAmount = value;
}

void Morozov::Controller::setRequestsNumber(int value)
{
    requestsNumber = value;
}

void Morozov::Controller::setBuffersAmount(int value)
{
    buffersAmount = value;
}

void Morozov::Controller::setSourcesAmount(int value)
{
    sourcesAmount = value;
}

void Morozov::Controller::setLambda(int value)
{
    lambda = value;
}

void Morozov::Controller::setBeta(int value)
{
    beta = value;
}

void Morozov::Controller::setAlpha(int value)
{
    alpha = value;
}
