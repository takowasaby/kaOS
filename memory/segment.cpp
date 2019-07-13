#include "segment.h"

Segment::Segment(unsigned int segmentDescriptorTableAddress) :
    gdt_(reinterpret_cast<SegmentDescriptorTable *>(segmentDescriptorTableAddress)),
    gdtSize_(0)
{
    new(gdt_) SegmentDescriptorTable();
}

void Segment::setKernelSegment(unsigned int limit, int base)
{
    gdt_->set(gdtSize_, limit, base, SegmentDescriptorTable::SYSTEM_RW_AR);
    ++gdtSize_;

}
