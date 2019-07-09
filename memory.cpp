#include "memory.h"

bool Memory::FreeListElement::allocate(unsigned int size, unsigned int allocateLimit)
{
    if (!isAllocable(size, allocateLimit)) return false;
    if (getSize() - makeAllocateSize(size) >= sizeof(FreeListElement))
    {
        unsigned int willAllocateSize = makeTotalUseMemorySize(makeAllocateSize(size));
        
        FreeListElement *remainFreeMemory = reinterpret_cast<FreeListElement *>(reinterpret_cast<unsigned int>(this) + willAllocateSize);
        remainFreeMemory->size_ = getSize() - willAllocateSize;
        remainFreeMemory->prev_ = this->prev_;
        remainFreeMemory->next_ = this->next_;

        this->prev_->next_ = remainFreeMemory;
        this->next_->prev_ = remainFreeMemory;

        this->size_ = makeAllocateSize(size);
        *endToStoreSize() = makeAllocateSize(size);
    }
    else if (getSize() == FREE_LIST_END_SIZE)
    {
        unsigned int willAllocateSize = makeTotalUseMemorySize(makeAllocateSize(size));

        FreeListElement *freeListEnd = reinterpret_cast<FreeListElement *>(reinterpret_cast<unsigned int>(this) + willAllocateSize);
        freeListEnd->prev_ = this->prev_;
        freeListEnd->markFreeListEnd();

        this->prev_->next_ = freeListEnd;

        this->size_ = makeAllocateSize(size);
        *endToStoreSize() = makeAllocateSize(size);
    }
    else
    {
        this->prev_->next_ = this->next_;
        this->next_->prev_ = this->prev_;
        markUsed();
    }
    return true;
}

bool Memory::FreeListElement::free(unsigned int beginMemoryArea, unsigned int allocateLimit)
{
    if (!isFreeable(allocateLimit)) return false;
    if (size_ & FREE_MEMORY_BIT || size_ == FREE_LIST_END_SIZE) return false;
    FreeListElement *freeMemoryElement = this;
    unsigned int *prevAreaElemSize = reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned int>(this) - sizeof(unsigned int));
    if (*prevAreaElemSize & FREE_MEMORY_BIT && 
        reinterpret_cast<unsigned int>(prevAreaElemSize) >= beginMemoryArea)
    {
        freeMemoryElement = reinterpret_cast<FreeListElement *>(reinterpret_cast<unsigned int>(this) - makeTotalUseMemorySize((*prevAreaElemSize) & GET_SIZE_MASK));
        freeMemoryElement->size_ += getTotalUseMemorySize();
        freeMemoryElement->next_ = this->next_;
        this->next_->prev_ = freeMemoryElement;
    }
    FreeListElement *nextAreaElem = reinterpret_cast<FreeListElement *>(reinterpret_cast<unsigned int>(this) + getTotalUseMemorySize());
    if (nextAreaElem->size_ & FREE_MEMORY_BIT)
    {
        if (nextAreaElem->getSize() == FREE_LIST_END_SIZE)
        {
            freeMemoryElement->markFreeListEnd();
            return true;
        }
        else
        {
            freeMemoryElement->size_ += nextAreaElem->getTotalUseMemorySize();
            freeMemoryElement->next_ = nextAreaElem->next_;
            nextAreaElem->next_->prev_ = freeMemoryElement;
        }
    }
    freeMemoryElement->markFree();
    return true;
}

unsigned int Memory::FreeListElement::getSize() const
{
    return size_ & GET_SIZE_MASK;
}

unsigned int Memory::FreeListElement::getTotalUseMemorySize() const
{
    return makeTotalUseMemorySize(getSize());
}

Memory::FreeListElement *Memory::FreeListElement::getNext()
{
    return next_;
}

void Memory::FreeListElement::initializeFreeList(Memory::FreeListElement *entry)
{
    prev_ = entry;
    entry->next_ = this;
    markFreeListEnd();
}

void Memory::FreeListElement::markFree()
{
    size_ |= FREE_MEMORY_BIT;
    *endToStoreSize() |= FREE_MEMORY_BIT;
}

void Memory::FreeListElement::markUsed()
{
    size_ &= GET_SIZE_MASK;
    *endToStoreSize() &= GET_SIZE_MASK;
}

void Memory::FreeListElement::markFreeListEnd()
{
    size_ = FREE_LIST_END_SIZE | FREE_MEMORY_BIT;
    next_ = nullptr;
}

bool Memory::FreeListElement::isAllocable(unsigned int size, unsigned int allocateLimit) const
{
    if (size == 0) return false;
    if ((size_ & FREE_MEMORY_BIT) != FREE_MEMORY_BIT) return false;
    if (getSize() == FREE_LIST_END_SIZE && 
        reinterpret_cast<unsigned int>(reinterpret_cast<unsigned int>(this) + makeTotalUseMemorySize(makeAllocateSize(size))) <= allocateLimit) 
        return true;
    return makeAllocateSize(size) <= getSize();
}

bool Memory::FreeListElement::isFreeable(unsigned int allocateLimit)
{
    if (size_ < 16 || (size_ & 15) != 0) return false;
    if (reinterpret_cast<unsigned int>(this) + getTotalUseMemorySize() > allocateLimit) return false;
    if (size_ != (*endToStoreSize())) return false;
    return true;
}

unsigned int *Memory::FreeListElement::endToStoreSize()
{
    return reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned int>(this) + getSize() + sizeof(unsigned int));
}

unsigned int Memory::FreeListElement::makeAllocateSize(unsigned int size)
{
    return (size + 15) & 0xfffffff0;
}
unsigned int Memory::FreeListElement::makeTotalUseMemorySize(unsigned int size)
{
    return sizeof(unsigned int) + size + sizeof(unsigned int);
}

Memory::Memory(unsigned int memoryBeginAddress, unsigned int memoryEndAddress) :
    beginAddress_(memoryBeginAddress),
    endAddress_(memoryEndAddress),
    freeSize_(endAddress_ - beginAddress_),
    freeListEntry_()
{
    FreeListElement *beginElem = reinterpret_cast<FreeListElement *>(memoryBeginAddress);
    beginElem->initializeFreeList(&freeListEntry_);
}

void *Memory::allocate(unsigned int size)
{
    for (FreeListElement *elem = freeListEntry_.getNext(); 
        reinterpret_cast<unsigned int>(elem) < endAddress_ && elem != nullptr; 
        elem = elem->getNext())
    {
        if (elem->allocate(size, endAddress_))
        {
            freeSize_ -= elem->getTotalUseMemorySize();
            return reinterpret_cast<void*>(reinterpret_cast<unsigned int>(elem) + sizeof(unsigned int));
        }
    }
    return nullptr;
}

void Memory::free(void *address)
{
    unsigned int addressNumber = reinterpret_cast<unsigned int>(address);
    if (addressNumber < beginAddress_ || endAddress_ < addressNumber) return;
    FreeListElement *elem = reinterpret_cast<FreeListElement*>(addressNumber - sizeof(unsigned int));
    unsigned int freeSize = elem->getTotalUseMemorySize();
    if (elem->free(beginAddress_, endAddress_))
    {
        freeSize_ += freeSize;
    }
}

unsigned int Memory::getTotalSize()
{
    return endAddress_ - beginAddress_;
}

unsigned int Memory::getFreeSize()
{
    return freeSize_;
}

unsigned int Memory::checkAllocableSize(unsigned int checkBeginAddress, unsigned int checkEndAddress)
{
    char flg486 = 0;
	unsigned int eflg;

	eflg = io_load_eflags();
	eflg |= EFLAGS_AC_BIT;
	io_store_eflags(eflg);
	eflg = io_load_eflags();
	if ((eflg & EFLAGS_AC_BIT) != 0)
	{
		flg486 = 1;
	}
	eflg &= ~EFLAGS_AC_BIT;
	io_store_eflags(eflg);

	if (flg486 != 0)
	{
		unsigned int cr0 = load_cr0();
		cr0 |= CR0_CACHE_DISABLE;
		store_cr0(cr0);
	}

	unsigned int result = memtest_sub(checkBeginAddress, checkEndAddress);

	if (flg486 != 0)
	{
		unsigned int cr0 = load_cr0();
		cr0 &= ~CR0_CACHE_DISABLE;
		store_cr0(cr0);
	}

	return result;
}