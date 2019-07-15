#include "mouse.h"

Mouse::Mouse(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber) :
    kbc_(kbc)
{
    interupt.enableMouseInterupt(kernelSegmentNumber);
    kbc_->setMode(KBC::KBC_MODE);
    kbc_->enableMouse();
}