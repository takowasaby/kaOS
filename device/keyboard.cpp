#include "keyboard.h"

Keyboard::Keyboard(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber) :
    kbc_(kbc)
{
    interupt.enableKeyboardInterupt(kernelSegmentNumber);
}
