#ifndef BUFFER_H
#define BUFFER_H

#include "request.h"
#include <vector>

namespace Morozov {
class Buffer
{
public:
    Buffer();
    Buffer(int size);

    bool isFreeBuff();
    bool isEmptyBuff();

    int addNewRequest(Request request);
    Request deleteOldRequest();
    Request getRequest();
private:
    int size;

    std::vector<Request *> buffers;

    int cursor = 0;
};
}

#endif // BUFFER_H
