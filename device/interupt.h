#include "interuptDescriptorTable.h"

class Interupt
{
public:
    constexpr static unsigned int INTERUPT_DESCRIPTOR_TABLE_BYTE_SIZE = sizeof(InteruptDescriptorTable);
    constexpr static unsigned int INTERUPT_DESCRIPTOR_TABLE_ADDRES = 0x0026f800;

    explicit Interupt(unsigned int interuptDescriptorTableAddress);

private:
    InteruptDescriptorTable *idt_;
    unsigned int idtSize_;

};