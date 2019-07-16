#include "interuptHandler.h"
#include "interupt.h"

void inthandler20(int *esp)
{
    Interupt::getInsPtr()->onInterupt(32, esp);
}

void inthandler21(int *esp)
{
    Interupt::getInsPtr()->onInterupt(33, esp);
}

void inthandler27(int *esp)
{
    Interupt::getInsPtr()->onInterupt(39, esp);
}

void inthandler2c(int *esp)
{
    Interupt::getInsPtr()->onInterupt(44, esp);
}