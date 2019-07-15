#pragma once

#include "kbc.h"
#include "interupt.h"

class Interupt;

class Mouse
{
public:
    Mouse();
    Mouse(KBC *kbc, Interupt &interupt, unsigned int kernelSegmentNumber);

private:
    KBC *kbc_;

};