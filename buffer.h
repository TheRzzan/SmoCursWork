#ifndef BUFFER_H
#define BUFFER_H

#include "request.h"
#include <list>

namespace Morozov {
class Buffer
{
public:
    Buffer();
    Buffer(int size);

    void addNewRequest(Request request);
    Request getRequest();
private:
    int size;

    std::list<int> buffers;
};
}

#endif // BUFFER_H
