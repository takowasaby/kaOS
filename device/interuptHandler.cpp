#include "interuptHandler.h"

#include "../debug.h"

void inthandler20(int *esp)
{
    Pic::getInteruptNotice(Pic::IRQ::TIMER);
    InteruptInfo info = {0};
    (reinterpret_cast<Queue<InteruptInfo> *>(INTERUPT_BUFFER_ADDRESS))->enqueue(info);
}

void inthandler21(int *esp)
{
    Pic::getInteruptNotice(Pic::IRQ::KEYBOARD);
    InteruptInfo info = {1};
    (reinterpret_cast<Queue<InteruptInfo> *>(INTERUPT_BUFFER_ADDRESS))->enqueue(info);
}

void inthandler27(int *esp)
{
    Pic::getInteruptNotice(Pic::IRQ::MOUSE);
    InteruptInfo info = {7};
    (reinterpret_cast<Queue<InteruptInfo> *>(INTERUPT_BUFFER_ADDRESS))->enqueue(info);
}

void inthandler2c(int *esp)
{
    Pic::getInteruptNotice(Pic::IRQ::PARALLEL);
    InteruptInfo info = {12};
    (reinterpret_cast<Queue<InteruptInfo> *>(INTERUPT_BUFFER_ADDRESS))->enqueue(info);
}