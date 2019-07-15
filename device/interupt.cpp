#include "interupt.h"

Interupt::Interupt(unsigned int interuptDescriptorTableAddress, unsigned char pic0INTFirst, unsigned char pic1INTFirst) :
    idt_(reinterpret_cast<InteruptDescriptorTable *>(interuptDescriptorTableAddress)),
    pic_(pic0INTFirst, pic1INTFirst),
    idtSize_(0),
    pic0INTFirst_(pic0INTFirst),
    pic1INTFirst_(pic1INTFirst)
{
    new(idt_) InteruptDescriptorTable();
    idt_->set(pic0INTFirst_ + static_cast<int>(Pic::IRQ::PARALLEL), reinterpret_cast<int>(asm_inthandler27), 2 << 3, InteruptDescriptorTable::INT_GATE_AR);
}

void Interupt::enableMouseInterupt()
{
    idt_->set(pic1INTFirst_ + static_cast<int>(Pic::IRQ::MOUSE) % 8, reinterpret_cast<int>(asm_inthandler2c), 2 << 3, InteruptDescriptorTable::INT_GATE_AR);
    pic_.enableInterupt(Pic::IRQ::MOUSE);
}

void Interupt::enableKeyboardInterupt()
{
    idt_->set(pic0INTFirst_ + static_cast<int>(Pic::IRQ::KEYBOARD), reinterpret_cast<int>(asm_inthandler21), 2 << 3, InteruptDescriptorTable::INT_GATE_AR);
    pic_.enableInterupt(Pic::IRQ::KEYBOARD);
}

void Interupt::enableTimerInterupt()
{
    idt_->set(pic0INTFirst_ + static_cast<int>(Pic::IRQ::TIMER), reinterpret_cast<int>(asm_inthandler20), 2 << 3, InteruptDescriptorTable::INT_GATE_AR);
    pic_.enableInterupt(Pic::IRQ::TIMER);
}