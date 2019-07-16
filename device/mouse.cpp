#include "mouse.h"

#include "../debug.h"

Mouse::Mouse(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber) :
    kbc_(kbc)
{
    interupt.enableMouseInterupt(kernelSegmentNumber);
    interupt.setDevice(0x2c, this);
    kbc_->setMode(KBC::KBC_MODE);
    kbc_->enableMouse();
}

void Mouse::onInterupt(int *esp)
{
    unsigned char keycode = kbc_->getKeyCode();
    char s[32];
    sprintf(s, "%d ", keycode);
    Buffer::getInsPtr()->buff(s);
}