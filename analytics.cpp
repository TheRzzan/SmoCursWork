#include "analytics.h"

Morozov::Analytics::Analytics()
{

}

void Morozov::Analytics::newRequestGenerate(Morozov::Request request)
{
    analytics.push_back(std::make_pair(std::make_pair(request, -1), NEW_REQ));
}

void Morozov::Analytics::addRequestToBuff(Morozov::Request request, int buff)
{
    analytics.push_back(std::make_pair(std::make_pair(request, buff), ADD_TO_BUFF));
}

void Morozov::Analytics::removeRequestFromBuff(Morozov::Request request, int buff)
{
    analytics.push_back(std::make_pair(std::make_pair(request, buff), REMOVE_FROM_BUFF));
}

void Morozov::Analytics::getRequestFromBuff(Morozov::Request request, int buff)
{
    analytics.push_back(std::make_pair(std::make_pair(request, buff), GET_FROM_BUFF));
}

void Morozov::Analytics::addRequestToDevice(Morozov::Request request, int device)
{
    analytics.push_back(std::make_pair(std::make_pair(request, device), ADD_TO_DEVICE));
}

void Morozov::Analytics::removeRequestFromDevice(Morozov::Request request, int device)
{
    analytics.push_back(std::make_pair(std::make_pair(request, device), REMOVE_FROM_DEVICE));
}

void Morozov::Analytics::beginTransaction()
{
    sourcesAmount = 0;
    buffersAmount = 0;
    devicesAmount = 0;
    analytics.clear();
    req_proc.clear();
    req_fail.clear();
    time_in_system.clear();
    time_of_wait.clear();
    time_of_process.clear();
    disp_tow.clear();
    disp_top.clear();
    prob_of_fail.clear();
    deviceLoad.clear();
    steps.clear();
}

bool Morozov::Analytics::config(int sourcesAmount, int buffersAmount, int devicesAmount)
{
    if (sourcesAmount > 0 && buffersAmount > 0 && devicesAmount > 0) {
        this->sourcesAmount = sourcesAmount;
        this->buffersAmount = buffersAmount;
        this->devicesAmount = devicesAmount;
        return true;
    } else {
        return false;
    }
}

void Morozov::Analytics::commit()
{
    std::vector<std::string> sourcesVec;
    std::vector<std::string> buffersVec;
    std::vector<std::string> devicesVec;
    std::vector<std::string> canceledVec;

    for (int i = 0; i < sourcesAmount; i++) {
        sourcesVec.push_back("null");
    }

    for (int i = 0; i < buffersAmount; i++) {
        buffersVec.push_back("null");
    }

    for (int i = 0; i < devicesAmount; i++) {
        devicesVec.push_back("null");
    }

    steps.push_back(StepModel(sourcesVec,
                    buffersVec,
                    devicesVec,
                    canceledVec));

    for (auto it = analytics.begin(); it!= analytics.end(); ++it) {
        std::pair<Request, int> reqPair = (*it).first;

        switch ((*it).second) {
        case NEW_REQ:
        {
            for (size_t i = 0; i < sourcesVec.size(); i ++) {
                if (i == (reqPair.first.getSourceId() - 1)) {
                    sourcesVec.at(i) =
                            std::to_string(reqPair.first.getSourceId()) +
                            "." +
                            std::to_string(reqPair.first.getRequestNumber());
                } else {
                    sourcesVec.at(i) = "null";
                }
            }
            steps.push_back(StepModel(sourcesVec,
                            buffersVec,
                            devicesVec,
                            canceledVec));
        }break;
        case ADD_TO_BUFF:
        {
            for (size_t i = 0; i < buffersVec.size(); i ++) {
                if (i == (reqPair.second)) {
                    buffersVec.at(i) =
                            std::to_string(reqPair.first.getSourceId()) +
                            "." +
                            std::to_string(reqPair.first.getRequestNumber());
                }
            }
            for (size_t i = 0; i < sourcesVec.size(); i ++) {
                if (i == (reqPair.first.getSourceId() - 1)) {
                    sourcesVec.at(i) = "null";
                }
            }
        }break;
        case REMOVE_FROM_BUFF:
        {
            for (size_t i = 0; i < buffersVec.size(); i ++) {
                if (i == (reqPair.second)) {
                    buffersVec.at(i) = "null";
                    canceledVec.push_back(
                            std::to_string(reqPair.first.getSourceId()) +
                            "." +
                            std::to_string(reqPair.first.getRequestNumber()));
                }
            }
        }break;
        case GET_FROM_BUFF:
        {
            for (size_t i = 0; i < buffersVec.size(); i ++) {
                if (i == (reqPair.second)) {
                    buffersVec.at(i) = "null";
                }
            }
        }break;
        case ADD_TO_DEVICE:
        {
            for (size_t i = 0; i < devicesVec.size(); i ++) {
                if (i == (reqPair.second - 1)) {
                    devicesVec.at(i) =
                            std::to_string(reqPair.first.getSourceId()) +
                            "." +
                            std::to_string(reqPair.first.getRequestNumber());
                }
            }
            for (size_t i = 0; i < sourcesVec.size(); i ++) {
                if (i == (reqPair.first.getSourceId() - 1)) {
                    sourcesVec.at(i) = "null";
                }
            }
            steps.push_back(StepModel(sourcesVec,
                            buffersVec,
                            devicesVec,
                            canceledVec));
        }break;
        case REMOVE_FROM_DEVICE:
        {
            for (size_t i = 0; i < devicesVec.size(); i ++) {
                if (i == (reqPair.second - 1)) {
                    devicesVec.at(i) = "null";
                }
            }
            steps.push_back(StepModel(sourcesVec,
                            buffersVec,
                            devicesVec,
                            canceledVec));
        }break;
        }
    }
}

std::vector<Morozov::Analytics::StepModel> Morozov::Analytics::getSteps() const
{
    return steps;
}

std::vector<float> Morozov::Analytics::getDeviceLoad() const
{
    return deviceLoad;
}

std::vector<float> Morozov::Analytics::getProb_of_fail() const
{
    return prob_of_fail;
}

std::vector<float> Morozov::Analytics::getDisp_top() const
{
    return disp_top;
}

std::vector<float> Morozov::Analytics::getDisp_tow() const
{
    return disp_tow;
}

std::vector<float> Morozov::Analytics::getTime_of_process() const
{
    return time_of_process;
}

std::vector<float> Morozov::Analytics::getTime_of_wait() const
{
    return time_of_wait;
}

std::vector<float> Morozov::Analytics::getTime_in_system() const
{
    return time_in_system;
}

std::vector<int> Morozov::Analytics::getReq_fail() const
{
    return req_fail;
}

std::vector<int> Morozov::Analytics::getReq_proc() const
{
    return req_proc;
}
