#include "interupt.h"

Interupt::Interupt(unsigned int interuptDescriptorTableAddress) :
    idt_(reinterpret_cast<InteruptDescriptorTable *>(interuptDescriptorTableAddress)),
    idtSize_(0)
{
    new(idt_) InteruptDescriptorTable();
}