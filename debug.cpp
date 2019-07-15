#include "debug.h"

Buffer *Buffer::getInsPtr()
{
    return reinterpret_cast<Buffer *>(Buffer::BUFFER_ADDRESS);
}

void Buffer::buff(const char *message)
{
    strcpy(buf_ + end_, message);
    end_ += strlen(message);
}
char *Buffer::out()
{
    return buf_;
}
bool Buffer::empty()
{
    return end_ == 0;
}
void Buffer::reset()
{
    end_ = 0;
}