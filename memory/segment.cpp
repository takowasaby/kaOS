#include "segment.h"

Segment::Segment(unsigned int segmentDescriptorTableAddress) :
    gdt_(reinterpret_cast<SegmentDescriptorTable *>(segmentDescriptorTableAddress)),
    gdtSize_(1)
{
    new(gdt_) SegmentDescriptorTable();
    gdt_->set(gdtSize_++, 0xffffffff, 0x00000000, SegmentDescriptorTable::SYSTEM_RW_AR);
}

void Segment::setKernelSegment(unsigned int limit, int base)
{
    gdt_->set(gdtSize_++, limit, base, SegmentDescriptorTable::SYSTEM_RX_AR);

}
