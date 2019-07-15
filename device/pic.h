#pragma once

#include "../naskfunc.h"

class Pic
{
public:
    enum class IRQ
    {
        TIMER,
        KEYBOARD,
        SLAVE_CASCADE,
        COM2,
        COM1,
        EXPAND_ISA_PCI_1,
        FDC,
        PARALLEL,
        RTC,
        EXPAND_ISA_PCI_2,
        EXPAND_ISA_PCI_3,
        NO_USE,
        MOUSE,
        FPU,
        ATA0,
        ATA1,
    };

    Pic(unsigned char pic0INTFirst, unsigned char pic1INTFirst);
    void enableInterupt(IRQ irq);

    static void getInteruptNotice(IRQ irq);

private:
    constexpr static unsigned short PIC0_ICW1 = 0x0020;
    constexpr static unsigned short PIC0_OCW2 = 0x0020;
    constexpr static unsigned short PIC0_IMR  = 0x0021;
    constexpr static unsigned short PIC0_ICW2 = 0x0021;
    constexpr static unsigned short PIC0_ICW3 = 0x0021;
    constexpr static unsigned short PIC0_ICW4 = 0x0021;
    constexpr static unsigned short PIC1_ICW1 = 0x00a0;
    constexpr static unsigned short PIC1_OCW2 = 0x00a0;
    constexpr static unsigned short PIC1_IMR  = 0x00a1;
    constexpr static unsigned short PIC1_ICW2 = 0x00a1;
    constexpr static unsigned short PIC1_ICW3 = 0x00a1;
    constexpr static unsigned short PIC1_ICW4 = 0x00a1;

    unsigned int pic0IMRCache_;
    unsigned int pic1IMRCache_;

};