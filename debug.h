#pragma once

#include <string.h>
#include <stdio.h>

class Buffer
{
private:
    constexpr static unsigned int BUFFER_ADDRESS = 0x0fe0;
    char buf_[2048];
    unsigned int end_ = 0;
public:
    static Buffer *getInsPtr();
    void buf(const char *message);
    char *out();
    void reset();
};