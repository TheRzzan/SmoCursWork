#include "buffer.h"

Morozov::Buffer::Buffer()
{
    this->size = 0;
}

Morozov::Buffer::Buffer(int size)
{
    this->size = size;
    for (int i = 0; i < size; i++) {
        buffers.push_back(nullptr);
    }
}

bool Morozov::Buffer::isFreeBuff()
{
    bool res = false;
    for (int i = 0; i < size; i++) {
        if (buffers.at(i) == nullptr)
            res = true;
    }
    return res;
}

bool Morozov::Buffer::isEmptyBuff()
{
    bool res = true;
    for (int i = 0; i < size; i++) {
        if (buffers.at(i) != nullptr)
            res = false;
    }
    return res;
}

int Morozov::Buffer::addNewRequest(Morozov::Request request)
{
    for (int i = 0; i < size; i++) {
        if (buffers.at(i) == nullptr) {
            buffers.at(i) = new Request(request.getTimeOfWait(), request.getSourceId(), request.getRequestNumber());
            return i + 1;
        }
    }

    return -1;
}

Morozov::Request Morozov::Buffer::deleteOldRequest()
{
    for (int i = 0; i < size; i++) {
        if (buffers.at(i) != nullptr) {
            Request req = *buffers.at(i);
            buffers.at(i) = nullptr;
            return req;
        }
    }

    return Request();
}

Morozov::Request Morozov::Buffer::getRequest()
{
    for (int i = 0; i < size; i++) {
        if (cursor >= size || cursor < 0) {
            cursor = 0;
        }
        if (buffers.at(cursor) != nullptr) {
            Request req = *buffers.at(cursor);
            buffers.at(cursor) = nullptr;
            cursor++;
            return req;
        }
        cursor++;
    }

    return Request();
}
