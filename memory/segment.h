#include "segmentDescriptorTable.h"

class Segment
{
public:
    constexpr static unsigned int SEGMENT_DESCRIPTOR_TABLE_BYTE_SIZE = sizeof(SegmentDescriptorTable);
    constexpr static unsigned int SEGMENT_DESCRIPTOR_TABLE_ADDRES = 0x00270000;

    explicit Segment(unsigned int segmentDescriptorTableAddress);
    void setKernelSegment(unsigned int limit, int base);

private:
    SegmentDescriptorTable *gdt_;
    unsigned int gdtSize_;

};