#include "interupt.h"

Interupt::Interupt(unsigned int interuptDescriptorTableAddress, unsigned char pic0INTFirst, unsigned char pic1INTFirst) :
    idt_(reinterpret_cast<InteruptDescriptorTable *>(interuptDescriptorTableAddress)),
    pic_(pic0INTFirst, pic1INTFirst),
    idtSize_(0)
{
    new(idt_) InteruptDescriptorTable();
}

void Interupt::enableMouseInterupt()
{
    pic_.enableInterupt(Pic::IRQ::MOUSE);
}

void Interupt::enableKeyboardInterupt()
{
    pic_.enableInterupt(Pic::IRQ::KEYBOARD);
}

void Interupt::enableTimerInterupt()
{
    pic_.enableInterupt(Pic::IRQ::TIMER);
}