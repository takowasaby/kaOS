#pragma once

#include "interuptDescriptorTable.h"
#include "interuptHandler.h"
#include "pic.h"
#include "../vec.h"

class Interupt
{
public:
    constexpr static unsigned int INTERUPT_DESCRIPTOR_TABLE_BYTE_SIZE = sizeof(InteruptDescriptorTable);
    constexpr static unsigned int INTERUPT_DESCRIPTOR_TABLE_ADDRES = 0x0026f800;
    constexpr static unsigned char PIC0_FIRST_INTERUPT_NUMBER = 0x20;
    constexpr static unsigned char PIC1_FIRST_INTERUPT_NUMBER = 0x28;

    static Interupt *getInsPtr();

    class IDevice
    {
    public:
        //virtual ~IDevice();
        virtual void onInterupt(int *esp) = 0;
    };

    explicit Interupt(unsigned int interuptDescriptorTableAddress, unsigned char pic0INTFirst, unsigned char pic1INTFirst);
    void enableMouseInterupt(unsigned int segmentationNumber);
    void enableKeyboardInterupt(unsigned int segmentationNumber);
    void enableTimerInterupt(unsigned int segmentationNumber);

    void setDevice(int interuptNumber, IDevice *device);
    void onInterupt(int interuptNumber, int *esp);

private:
    constexpr static unsigned int INTERUPT_INSTANCE_ADDRESS = 0x3000;

    struct DeviceHolder 
    {
        int interuptNumber_;
        IDevice *device_;
    };

    InteruptDescriptorTable *idt_;
    Pic pic_;
    Vec<DeviceHolder> devices_;
    unsigned int idtSize_;
    const unsigned char pic0INTFirst_;
    const unsigned char pic1INTFirst_;

};