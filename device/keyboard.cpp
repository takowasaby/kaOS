#include "keyboard.h"

#include "../debug.h"

Keyboard::Keyboard(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber) :
    kbc_(kbc)
{
    interupt.enableKeyboardInterupt(kernelSegmentNumber);
    interupt.setDevice(0x21, this);
}

void Keyboard::onInterupt(int *esp)
{
    unsigned char keycode = kbc_->getKeyCode();
    char s[32];
    sprintf(s, "%d ", keycode);
    Buffer::getInsPtr()->buff(s);
}
