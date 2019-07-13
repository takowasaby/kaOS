#include "segmentDescriptorTable.h"

#include "../debug.h"

SegmentDescriptorTable::SegmentDescriptorTable()
{
    for (unsigned int i = 0; i < MAX_SEGMENT_SIZE; i++)
    {
        descriptors[i].reset();
    }
    load_gdtr(sizeof(SegmentDescriptorTable), reinterpret_cast<int>(this));
}

void SegmentDescriptorTable::set(unsigned int index, unsigned int limit, int base, int accessRight)
{
    descriptors[index].set(limit, base, accessRight);
}

void SegmentDescriptorTable::SegmentDescriptor::set(unsigned int limit, int base, int accessRight)
{
    if (limit > 0xfffff) {
        accessRight |= 0x8000;
        limit /= 0x1000;
    }

    limit_low_ = limit & 0xffff;
    base_low_ = base & 0xffff;
    base_mid_ = (base >> 16) & 0xff;
    access_right_ = accessRight & 0xff;
    limit_high_ = ((limit >> 16) & 0x0f) | ((accessRight >> 8) & 0xf0);
    base_high_ = (base >> 24) & 0xff;
}

void SegmentDescriptorTable::SegmentDescriptor::reset()
{
    limit_low_ = 0;
    base_low_ = 0;
    base_mid_ = 0;
    access_right_ = 0;
    limit_high_ = 0;
    base_high_ = 0;
}