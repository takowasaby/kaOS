#include "segmentDescriptorTable.h"

class Segment
{
public:
    constexpr static unsigned int SEGMENT_DESCRIPTOR_TABLE_BYTE_SIZE = sizeof(SegmentDescriptorTable);
    constexpr static unsigned int SEGMENT_DESCRIPTOR_TABLE_ADDRES = 0x00270000;

    explicit Segment(unsigned int segmentDescriptorTableAddress);
    explicit Segment(unsigned int segmentDescriptorTableAddress, unsigned int kernelSegmentLimit, int kernelSegmentBase);
    
    unsigned int setKernelSegment(unsigned int limit, int base);
    unsigned int getKernelSegmentNumber();

private:
    SegmentDescriptorTable *gdt_;
    unsigned int gdtSize_;
    unsigned int kernelSegmentNumber_;

};