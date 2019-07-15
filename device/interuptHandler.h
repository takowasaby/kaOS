#pragma once

#include "../naskfunc.h"
#include "../queue.h"
#include "pic.h"

extern "C" 
{
    void asm_inthandler20(void);
    void asm_inthandler21(void);
    void asm_inthandler27(void);
    void asm_inthandler2c(void);
    
    void inthandler20(int *esp);
    void inthandler21(int *esp);
    void inthandler27(int *esp);
    void inthandler2c(int *esp);
}

struct InteruptInfo
{
    int interuptID_;
};

constexpr unsigned int INTERUPT_BUFFER_ADDRESS = 0x3000;