#include "buffer.h"

Morozov::Buffer::Buffer()
{
    this->size = 0;
}

Morozov::Buffer::Buffer(int size)
{
    this->size = size;
}

bool Morozov::Buffer::isFreeBuff()
{
    return buffers.size() != size;
}

bool Morozov::Buffer::isEmptyBuff()
{
    return buffers.size() <= 0;
}

int Morozov::Buffer::addNewRequest(Morozov::Request request)
{
    buffers.push_front(request);
    return buffers.size();
}

Morozov::Request Morozov::Buffer::deleteOldRequest()
{
    Request request = buffers.back();
    buffers.pop_back();
    return request;
}

Morozov::Request Morozov::Buffer::getRequest()
{
    Request request = buffers.front();
    buffers.pop_front();
    return request;
}
