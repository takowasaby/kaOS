#pragma once

#include <string.h>
#include <stdio.h>

class Buffer
{
private:
    constexpr static unsigned int BUFFER_ADDRESS = 0x1000;
    char buf_[4096];
    unsigned int end_ = 0;
public:
    static Buffer *getInsPtr();
    void buf(const char *message);
    char *out();
    void reset();
};