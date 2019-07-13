#include "interuptDescriptorTable.h"

#include "../debug.h"

InteruptDescriptorTable::InteruptDescriptorTable()
{
    for (unsigned int i = 0; i < MAX_SEGMENT_SIZE; i++)
    {
        descriptors[i].reset();
    }
    load_gdtr(sizeof(InteruptDescriptorTable), reinterpret_cast<int>(this));
}

void InteruptDescriptorTable::set(unsigned int index, unsigned int offset, int selector, int accessRight)
{
    descriptors[index].set(offset, selector, accessRight);
}

void InteruptDescriptorTable::InteruptDescriptor::set(unsigned int offset, int selector, int accessRight)
{
    offsetLow_ = offset & 0xffff;
    selector_ = selector;
    dwCount_ = (accessRight >> 8) & 0xff;
    accessRight_ = accessRight & 0xff;
    offsetHigh_ = (offset >> 16) & 0xffff;
}

void InteruptDescriptorTable::InteruptDescriptor::reset()
{
    offsetLow_ = 0;
    selector_ = 0;
    dwCount_ = 0;
    accessRight_ = 0;
    offsetHigh_ = 0;
}