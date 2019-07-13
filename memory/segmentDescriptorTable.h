#include "memory.h"
#include "../naskfunc.h"

class SegmentDescriptorTable
{
public:
    constexpr static int NO_USE_AR = 0x4000;
    constexpr static int SYSTEM_RW_AR = 0x4092;
    constexpr static int SYSTEM_RX_AR = 0x409a;
    constexpr static int APP_RW_AR = 0x40f2;
    constexpr static int APP_RX_AR = 0x40fa;
    
    constexpr static unsigned int MAX_SEGMENT_SIZE = 8192;

    SegmentDescriptorTable();
    void set(unsigned int index, unsigned int limit, int base, int accessRight);

private:
    class SegmentDescriptor
    {
    public:
        void set(unsigned int limit, int base, int accessRight);
        void reset();
    private:
        short limitLow_, baseLow_;
        char baseMid_, accessRight_, limitHigh_, baseHigh_;
    };

    SegmentDescriptor descriptors[MAX_SEGMENT_SIZE];
};