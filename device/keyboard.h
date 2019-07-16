#pragma once

#include "kbc.h"
#include "interupt.h"

class Keyboard : public Interupt::IDevice
{
public:
    Keyboard(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber);

    void onInterupt(int *esp) override;

private:
    KBC *kbc_;

};