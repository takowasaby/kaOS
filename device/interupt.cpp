#include "interupt.h"

#include "../debug.h"

Interupt *Interupt::getInsPtr()
{
    return *(reinterpret_cast<Interupt **>(INTERUPT_INSTANCE_ADDRESS));
}

Interupt::Interupt(unsigned int interuptDescriptorTableAddress, unsigned char pic0INTFirst, unsigned char pic1INTFirst) :
    idt_(reinterpret_cast<InteruptDescriptorTable *>(interuptDescriptorTableAddress)),
    pic_(pic0INTFirst, pic1INTFirst),
    devices_(),
    idtSize_(0),
    pic0INTFirst_(pic0INTFirst),
    pic1INTFirst_(pic1INTFirst)
{
    new(idt_) InteruptDescriptorTable();
    idt_->set(pic0INTFirst_ + static_cast<int>(Pic::IRQ::PARALLEL), reinterpret_cast<int>(asm_inthandler27), 2 << 3, InteruptDescriptorTable::INT_GATE_AR);
    *(reinterpret_cast<Interupt **>(INTERUPT_INSTANCE_ADDRESS)) = this;
}

void Interupt::enableMouseInterupt(unsigned int segmentationNumber)
{
    idt_->set(pic1INTFirst_ + static_cast<int>(Pic::IRQ::MOUSE) % Pic::IRQ_SIZE, reinterpret_cast<int>(asm_inthandler2c), segmentationNumber << 3, InteruptDescriptorTable::INT_GATE_AR);
    pic_.enableInterupt(Pic::IRQ::MOUSE);
}

void Interupt::enableKeyboardInterupt(unsigned int segmentationNumber)
{
    idt_->set(pic0INTFirst_ + static_cast<int>(Pic::IRQ::KEYBOARD), reinterpret_cast<int>(asm_inthandler21), segmentationNumber << 3, InteruptDescriptorTable::INT_GATE_AR);
    pic_.enableInterupt(Pic::IRQ::KEYBOARD);
}

void Interupt::enableTimerInterupt(unsigned int segmentationNumber)
{
    idt_->set(pic0INTFirst_ + static_cast<int>(Pic::IRQ::TIMER), reinterpret_cast<int>(asm_inthandler20), segmentationNumber << 3, InteruptDescriptorTable::INT_GATE_AR);
    pic_.enableInterupt(Pic::IRQ::TIMER);
}

void Interupt::setDevice(int interuptNumber, IDevice *device)
{
    DeviceHolder holder = { interuptNumber, device };
    int size = devices_.size();
    for (int i = 0; i < size; i++)
    {
        if (devices_[i].interuptNumber_ == interuptNumber)
        {
            devices_[i].device_ = device;
            return;
        }
    }
    devices_.push_back(holder);
}

void Interupt::onInterupt(int interuptNumber, int *esp)
{
    Buffer::getInsPtr()->buff("begin ");
    if (pic0INTFirst_ <= interuptNumber && interuptNumber < static_cast<int>(pic0INTFirst_ + Pic::IRQ_SIZE))
    {
        char s[32];
        sprintf(s, "%d ", interuptNumber - pic0INTFirst_);
        Buffer::getInsPtr()->buff(s);
        pic_.getInteruptNotice(static_cast<Pic::IRQ>(interuptNumber - pic0INTFirst_));
    }
    else if (pic1INTFirst_ <= interuptNumber && interuptNumber < static_cast<int>(pic1INTFirst_ + Pic::IRQ_SIZE))
    {
        char s[32];
        sprintf(s, "%d ", interuptNumber - pic1INTFirst_);
        Buffer::getInsPtr()->buff(s);
        pic_.getInteruptNotice(static_cast<Pic::IRQ>(interuptNumber - pic1INTFirst_ + Pic::IRQ_SIZE));
    }
    int size = devices_.size();
    for (int i = 0; i < size; i++)
    {
        if (devices_[i].interuptNumber_ == interuptNumber)
        {
            devices_[i].device_->onInterupt(esp);
            return;
        }
    }
    Buffer::getInsPtr()->buff("end ");
}