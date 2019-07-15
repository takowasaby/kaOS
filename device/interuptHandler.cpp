#include "interuptHandler.h"
#include "interupt.h"

#include "../debug.h"

void inthandler20(int *esp)
{
    Interupt::getInsPtr()->onInterupt(32, esp);
}

void inthandler21(int *esp)
{
    unsigned char keycode = io_in8(PORT_KEYDAT);
    char s[32];
    sprintf(s, "%d ", keycode);
    Buffer::getInsPtr()->buff(s);
    Interupt::getInsPtr()->onInterupt(33, esp);
}

void inthandler27(int *esp)
{
    Interupt::getInsPtr()->onInterupt(39, esp);
}

void inthandler2c(int *esp)
{
    unsigned char keycode = io_in8(PORT_KEYDAT);
    char s[32];
    sprintf(s, "%d ", keycode);
    Buffer::getInsPtr()->buff(s);
    Interupt::getInsPtr()->onInterupt(44, esp);
}