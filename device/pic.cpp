#include "pic.h"

Pic::Pic(unsigned char pic0INTFirst, unsigned char pic1INTFirst)
{
    io_out8(PIC1_IMR,  0xff  );
    io_out8(PIC1_IMR,  0xff  );

    io_out8(PIC0_ICW1, 0x11  );
    io_out8(PIC0_ICW2, pic0INTFirst);
    io_out8(PIC0_ICW3, 1 << 2);
    io_out8(PIC0_ICW4, 0x01  );

    io_out8(PIC1_ICW1, 0x11  );
    io_out8(PIC1_ICW2, pic1INTFirst);
    io_out8(PIC1_ICW3, 2     );
    io_out8(PIC1_ICW4, 0x01  );

    io_out8(PIC0_IMR,  0xfb  );
    io_out8(PIC1_IMR,  0xff  );
}

void Pic::enableInterupt(IRQ irq)
{
    unsigned char newPIC0IMR = pic0IMRCache_;
    unsigned char newPIC1IMR = pic1IMRCache_;
    unsigned char irqNum = static_cast<unsigned char>(irq);

    if (irqNum < 8) 
    {
        newPIC0IMR &= (0xff ^ (1 << irqNum));
        if (newPIC0IMR != pic0IMRCache_)
        {
            io_out8(PIC0_IMR, newPIC0IMR);
            pic0IMRCache_ = newPIC0IMR;
        }
    }
    else if (irqNum < 16)
    {
        irqNum -= 8;
        newPIC0IMR &= 0xfb;
        newPIC1IMR &= (0xff ^ (1 << irqNum));
        if (newPIC0IMR != pic0IMRCache_)
        {
            io_out8(PIC0_IMR, newPIC0IMR);
            pic0IMRCache_ = newPIC0IMR;
        }
        if (newPIC1IMR != pic1IMRCache_)
        {
            io_out8(PIC1_IMR, newPIC1IMR);
            pic1IMRCache_ = newPIC1IMR;
        }
    }
}