#pragma once

extern "C"
{
    void io_hlt(void);
    void io_cli(void);
    void io_out8(int port, int data);
    int  io_load_eflags(void);
    void io_store_eflags(int eflags);
    void load_gdtr(int limit, int addr);
    void load_idtr(int limit, int addr);
    int load_cr0(void);
    void store_cr0(int cr0);
    unsigned int memtest_sub(unsigned int start, unsigned int end);
};