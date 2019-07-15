#pragma once

#include "kbc.h"
#include "interupt.h"

class Interupt;

class Keyboard
{
public:
    Keyboard(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber);

private:
    KBC *kbc_;

};