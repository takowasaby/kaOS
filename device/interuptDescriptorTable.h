#include "../memory/memory.h"
#include "../naskfunc.h"

class InteruptDescriptorTable
{
public:
    constexpr static unsigned int MAX_SEGMENT_SIZE = 256;

    InteruptDescriptorTable();
    void set(unsigned int index, unsigned int offset, int selector, int accessRight);

private:
    class InteruptDescriptor
    {
    public:
        void set(unsigned int offset, int selector, int accessRight);
        void reset();
    private:
        short offsetLow_, selector_;
        char dwCount_, accessRight_; short offsetHigh_;
    };

    InteruptDescriptor descriptors[MAX_SEGMENT_SIZE];
};