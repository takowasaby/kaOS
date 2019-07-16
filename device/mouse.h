#pragma once

#include "kbc.h"
#include "interupt.h"

class Mouse : public Interupt::IDevice
{
public:
    Mouse(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber);

    void onInterupt(int *esp) override; 

private:
    KBC *kbc_;

};