#pragma once

#include "../naskfunc.h"

#include <string.h>
#include <stdio.h>

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
    void dumpMemoryMap(char *dump);

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
        bool free(unsigned int beginMemoryArea, unsigned int allocateLimit, FreeListElement* freeListFirst);
        unsigned int getSize() const;
        unsigned int getTotalUseMemorySize() const;
        FreeListElement *getNext();
        void initializeFreeList(FreeListElement *entry);

    private:
        void setSize(unsigned int size);

        void markFree();
        void markUsed();
        void markFreeListEnd();
        
        bool isAllocable(unsigned int size, unsigned int allocateLimit) const;
        bool isFreeable(unsigned int allocateLimit, FreeListElement* freeListFirst, FreeListElement** prev = nullptr);

        unsigned int *endToStoreSize();

        static unsigned int makeAllocateSize(unsigned int size);
        static unsigned int makeTotalUseMemorySize(unsigned int size);
    };

    const unsigned int beginAddress_;
    const unsigned int endAddress_;
    unsigned int freeSize_;
    FreeListElement freeListEntry_;

private:
    constexpr static unsigned int GLOBAL_MEMORY_ADDRESS = 0x2000;
public:
    static Memory *getInsPtr();
};



extern "C" {
    void *memcpy(void *__restrict__  s1, const void *__restrict__  s2, size_t n);
}

void *operator new(size_t size);
void *operator new(size_t size, void *p);
void *operator new[](size_t size);
void  operator delete(void *address);
void  operator delete(void *address, void *p);
void  operator delete[](void *address);

extern "C" {
    void *malloc(size_t size);
    void  free(void* address);
}