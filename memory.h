#include "naskfunc.h"

class Memory
{
public:
    constexpr static unsigned int EFLAGS_AC_BIT = 0x00040000;
    constexpr static unsigned int CR0_CACHE_DISABLE = 0x60000000;

    Memory(unsigned int memoryBeginAddress, unsigned int memoryEndAddress);
    void *allocate(unsigned int size);
    void free(void* address);
    unsigned int getTotalSize();
    unsigned int getFreeSize();

    static unsigned int checkAllocableSize(unsigned int checkBeginAddress, unsigned int checkEndAddress);

private:
    class FreeListElement
    {
        constexpr static unsigned int FREE_MEMORY_BIT = 0x00000001;
        constexpr static unsigned int GET_SIZE_MASK = 0xfffffffe;
        constexpr static unsigned int FREE_LIST_END_SIZE = 0x00000000;

        unsigned int size_;
        FreeListElement *prev_;
        FreeListElement *next_;
    public:
        bool allocate(unsigned int size, unsigned int allocateLimit);
        bool free(unsigned int beginMemoryArea, unsigned int allocateLimit);
        unsigned int getSize() const;
        unsigned int getTotalUseMemorySize() const;
        FreeListElement *getNext();
        void initializeFreeList(FreeListElement *entry);

    private:
        void markFree();
        void markUsed();
        void markFreeListEnd();
        
        bool isAllocable(unsigned int size, unsigned int allocateLimit) const;
        bool isFreeable(unsigned int allocateLimit);

        unsigned int *endToStoreSize();

        static unsigned int makeAllocateSize(unsigned int size);
        static unsigned int makeTotalUseMemorySize(unsigned int size);
    };

    const unsigned int beginAddress_;
    const unsigned int endAddress_;
    unsigned int freeSize_;
    FreeListElement freeListEntry_;
};