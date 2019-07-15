#include "segment.h"

#include "../debug.h"

Segment::Segment(unsigned int segmentDescriptorTableAddress) :
    gdt_(reinterpret_cast<SegmentDescriptorTable *>(segmentDescriptorTableAddress)),
    gdtSize_(1),
    kernelSegmentNumber_(0)
{
    new(gdt_) SegmentDescriptorTable();
    gdt_->set(gdtSize_++, 0xffffffff, 0x00000000, SegmentDescriptorTable::SYSTEM_RW_AR);
}

Segment::Segment(unsigned int segmentDescriptorTableAddress, unsigned int kernelSegmentLimit, int kernelSegmentBase) :
    Segment(segmentDescriptorTableAddress)
{
    kernelSegmentNumber_ = setKernelSegment(kernelSegmentLimit, kernelSegmentBase);
}

unsigned int Segment::getKernelSegmentNumber()
{
    return kernelSegmentNumber_;
}

unsigned int Segment::setKernelSegment(unsigned int limit, int base)
{
    gdt_->set(gdtSize_++, limit, base, SegmentDescriptorTable::SYSTEM_RX_AR);
    return gdtSize_ - 1;

}
