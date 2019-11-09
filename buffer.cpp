#include "buffer.h"

Morozov::Buffer::Buffer()
{
    this->size = 0;
}

Morozov::Buffer::Buffer(int size)
{
    this->size = size;
}

void Morozov::Buffer::addNewRequest(Morozov::Request request)
{
    if (buffers.size() == size)
        buffers.pop_back();

    buffers.push_front(request);
}

Morozov::Request Morozov::Buffer::getRequest()
{
    Request request = buffers.front();
    buffers.pop_front();
    return request;
}
