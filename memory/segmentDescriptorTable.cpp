#include "segmentDescriptorTable.h"

SegmentDescriptorTable::SegmentDescriptorTable()
{
    for (unsigned int i = 0; i < MAX_SEGMENT_SIZE; i++)
    {
        descriptors[i].reset();
    }
    load_gdtr(sizeof(SegmentDescriptorTable) - 1, reinterpret_cast<int>(this));
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

    limitLow_ = limit & 0xffff;
    baseLow_ = base & 0xffff;
    baseMid_ = (base >> 16) & 0xff;
    accessRight_ = accessRight & 0xff;
    limitHigh_ = ((limit >> 16) & 0x0f) | ((accessRight >> 8) & 0xf0);
    baseHigh_ = (base >> 24) & 0xff;
}

void SegmentDescriptorTable::SegmentDescriptor::reset()
{
    limitLow_ = 0;
    baseLow_ = 0;
    baseMid_ = 0;
    accessRight_ = 0;
    limitHigh_ = 0;
    baseHigh_ = 0;
}