#include "buffer.h"

Morozov::Buffer::Buffer()
{
    this->size = 0;
}

Morozov::Buffer::Buffer(int size)
{
    this->size = size;
    buffers.reserve(size);
}

bool Morozov::Buffer::isFreeBuff()
{
    return buffers.size() != size;
}

bool Morozov::Buffer::isEmptyBuff()
{
    return buffers.size() == 0;
}

int Morozov::Buffer::addNewRequest(Morozov::Request request)
{
    int i = 0;
    auto it = buffers.begin();
    for (; it != buffers.end(); ++it, i++) {
        if (*it == nullptr) {
            buffers.insert(it, &request);
            return i;
        }
    }
    return -1;
}

Morozov::Request Morozov::Buffer::deleteOldRequest()
{
    for (auto it = buffers.end(); it != buffers.begin() ; --it) {
        if (*it != nullptr) {
            Request req = **it;
            buffers.insert(it, nullptr);
            return req;
        }
    }
    return Request();
}

Morozov::Request Morozov::Buffer::getRequest()
{
    for (auto it = buffers.begin(); it != buffers.end() ; ++it) {
        if (*it != nullptr) {
            Request req = **it;
            buffers.insert(it, nullptr);
            return req;
        }
    }
    return Request();
}
