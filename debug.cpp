#include "debug.h"

Buffer *Buffer::getInsPtr()
{
    return reinterpret_cast<Buffer *>(Buffer::BUFFER_ADDRESS);
}

void Buffer::buf(const char *message)
{
    strcpy(buf_ + end_, message);
    end_ += strlen(message);
}
char *Buffer::out()
{
    return buf_;
}
void Buffer::reset()
{
    end_ = 0;
}